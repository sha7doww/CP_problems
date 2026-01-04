#!/bin/bash

# Algorithm Contest Problem Pipeline Script
# Author: CP Problems Management System
# Description: Automated data generation and validation pipeline

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check if we're in a problem directory
check_problem_directory() {
    if [[ ! -f "statement.md" ]]; then
        print_error "No statement.md found. Please run this script from a problem directory."
        exit 1
    fi
    print_status "Detected problem directory: $(basename $(pwd))"
}

# Compile C++ files with testlib
compile_cpp() {
    local file=$1
    local output=$2
    local use_debug=${3:-0}  # Third parameter: 1 for debug mode, 0 for normal

    if [[ -f "$file" ]]; then
        print_status "Compiling $file -> $output"

        # Use -D_GLIBCXX_DEBUG only for std.cpp, not for testlib components
        local debug_flag=""
        if [[ $use_debug -eq 1 ]]; then
            debug_flag="-D_GLIBCXX_DEBUG"
        fi

        if g++ -std=c++17 -O2 -Wall -Wextra $debug_flag -o "$output" "$file" 2>/dev/null; then
            print_success "Compiled $file successfully"
            return 0
        else
            print_error "Failed to compile $file"
            return 1
        fi
    else
        return 1
    fi
}

# Check if testlib.h exists
check_testlib() {
    local testlib_path="../../testlib.h"
    if [[ ! -f "$testlib_path" ]]; then
        print_error "testlib.h not found at $testlib_path"
        print_status "Please download testlib.h from: https://github.com/MikeMirzayanov/testlib"
        exit 1
    fi
}

# Compile all components
compile_all() {
    print_status "Starting compilation phase..."

    # Copy testlib.h to current directory if it exists in parent
    local testlib_source="../../testlib.h"
    if [[ -f "$testlib_source" ]]; then
        cp "$testlib_source" "./testlib.h"
    fi

    local compile_success=0

    # Compile standard programs
    # Compile TWO versions: std_debug (with bounds checking) and std_fast (for output generation)
    if [[ -f "std.cpp" ]]; then
        if compile_cpp "std.cpp" "std_debug" 1; then  # Debug mode for safety checking
            compile_success=$((compile_success + 1))
        fi
        if compile_cpp "std.cpp" "std_fast" 0; then  # Fast mode for output generation
            compile_success=$((compile_success + 1))
        fi
    fi

    if [[ -f "std.py" ]]; then
        print_status "Python std found, no compilation needed"
        compile_success=$((compile_success + 1))
    fi

    if [[ -f "std.java" ]]; then
        print_status "Compiling Java std..."
        if javac -encoding UTF-8 std.java 2>/dev/null; then
            print_success "Java std compiled successfully"
            compile_success=$((compile_success + 1))
        else
            print_error "Failed to compile Java std"
        fi
    fi

    # Compile generator (without debug mode for faster compilation)
    if [[ -f "generator.cpp" ]]; then
        if compile_cpp "generator.cpp" "generator" 0; then
            compile_success=$((compile_success + 1))
        fi
    fi

    # Compile validator (without debug mode)
    if [[ -f "validator.cpp" ]]; then
        if compile_cpp "validator.cpp" "validator" 0; then
            compile_success=$((compile_success + 1))
        fi
    fi

    # Compile checker (without debug mode)
    if [[ -f "checker.cpp" ]]; then
        if compile_cpp "checker.cpp" "checker" 0; then
            compile_success=$((compile_success + 1))
        fi
    fi

    if [[ $compile_success -eq 0 ]]; then
        print_error "No files were successfully compiled"
        exit 1
    fi

    print_success "Compilation phase completed ($compile_success files compiled)"
}

# Generate test data if generator exists
generate_data() {
    if [[ -f "generator" ]]; then
        print_status "Running data generation..."

        # Create data directory if it doesn't exist
        mkdir -p data

        # If there's a generate.sh script, use it
        if [[ -f "generate.sh" ]]; then
            print_status "Using custom generate.sh script"
            chmod +x generate.sh
            if ./generate.sh; then
                print_success "Data generation completed via generate.sh"
            else
                print_error "generate.sh failed"
                return 1
            fi
        else
            print_warning "generator.cpp found but no generate.sh script"
            print_status "Skipping automatic generation. Please create generate.sh or generate manually."
        fi
    else
        print_status "No generator found, skipping data generation"
    fi
}

# Validate all input files
validate_data() {
    if [[ ! -f "validator" ]]; then
        print_warning "No validator found, skipping input validation"
        return 0
    fi

    print_status "Validating input files..."

    local validation_errors=0
    local total_files=0

    # Find all .in files in data directory
    for infile in data/*.in; do
        if [[ -f "$infile" ]]; then
            total_files=$((total_files + 1))
            local filename=$(basename "$infile")
            print_status "Validating $filename..."

            if ./validator < "$infile" 2>/dev/null; then
                print_success "✓ $filename is valid"
            else
                print_error "✗ $filename is INVALID"
                validation_errors=$((validation_errors + 1))
            fi
        fi
    done

    if [[ $total_files -eq 0 ]]; then
        print_warning "No .in files found in data/ directory"
    elif [[ $validation_errors -eq 0 ]]; then
        print_success "All $total_files input files passed validation"
    else
        print_error "$validation_errors/$total_files input files failed validation"
        return 1
    fi
}

# Generate outputs from inputs using std programs
generate_outputs() {
    print_status "Generating outputs from inputs..."

    local output_errors=0
    local total_files=0

    # Find all .in files in data directory
    for infile in data/*.in; do
        if [[ -f "$infile" ]]; then
            total_files=$((total_files + 1))
            local basename=$(basename "$infile" .in)
            local outfile="data/$basename.out"

            print_status "Processing $basename.in -> $basename.out..."

            # Try different std programs in order of preference
            # Use std_fast (optimized) for speed, fall back to std_debug if needed
            local success=0

            if [[ -f "std_fast" ]]; then
                if timeout 60s ./std_fast < "$infile" > "$outfile" 2>/dev/null; then
                    print_success "✓ Generated $basename.out (C++ std_fast)"
                    success=1
                else
                    print_warning "C++ std_fast failed for $basename.in"
                fi
            fi

            # Fallback to debug version with longer timeout
            if [[ $success -eq 0 && -f "std_debug" ]]; then
                if timeout 120s ./std_debug < "$infile" > "$outfile" 2>/dev/null; then
                    print_success "✓ Generated $basename.out (C++ std_debug)"
                    success=1
                else
                    print_warning "C++ std_debug failed for $basename.in"
                fi
            fi

            if [[ $success -eq 0 && -f "std.py" ]]; then
                if timeout 30s python3 std.py < "$infile" > "$outfile" 2>/dev/null; then
                    print_success "✓ Generated $basename.out (Python std)"
                    success=1
                else
                    print_warning "Python std failed for $basename.in"
                fi
            fi

            if [[ $success -eq 0 && -f "std.class" ]]; then
                if timeout 30s java std < "$infile" > "$outfile" 2>/dev/null; then
                    print_success "✓ Generated $basename.out (Java std)"
                    success=1
                else
                    print_warning "Java std failed for $basename.in"
                fi
            fi

            if [[ $success -eq 0 ]]; then
                print_error "✗ Failed to generate $basename.out (no working std)"
                output_errors=$((output_errors + 1))
                # Remove potentially corrupted output file
                rm -f "$outfile"
            fi
        fi
    done

    if [[ $total_files -eq 0 ]]; then
        print_warning "No .in files found for output generation"
    elif [[ $output_errors -eq 0 ]]; then
        print_success "Successfully generated all $total_files output files"
    else
        print_error "Failed to generate $output_errors/$total_files output files"
        return 1
    fi
}

# Verify sample outputs using debug version (with bounds checking)
verify_samples_with_debug() {
    if [[ ! -f "std_debug" ]]; then
        return 0
    fi

    print_status "Verifying sample outputs with debug build (bounds checking)..."

    local verify_errors=0

    # Only verify sample files (they should be small and fast even with debug)
    for infile in data/sample_*.in; do
        if [[ -f "$infile" ]]; then
            local basename=$(basename "$infile" .in)
            local outfile="data/$basename.out"

            if [[ -f "$outfile" ]]; then
                print_status "Verifying $basename with debug build..."

                local debug_out=$(mktemp)
                if timeout 60s ./std_debug < "$infile" > "$debug_out" 2>/dev/null; then
                    if diff -q "$outfile" "$debug_out" > /dev/null 2>&1; then
                        print_success "✓ $basename passed debug verification"
                    else
                        print_error "✗ $basename: debug output differs from fast output!"
                        verify_errors=$((verify_errors + 1))
                    fi
                else
                    print_warning "Debug build timed out for $basename (skipping)"
                fi
                rm -f "$debug_out"
            fi
        fi
    done

    if [[ $verify_errors -gt 0 ]]; then
        print_error "Debug verification found $verify_errors mismatches!"
        return 1
    fi
}

# Check outputs with checker if available
check_outputs() {
    if [[ ! -f "checker" ]]; then
        print_status "No checker found, skipping output verification"
        return 0
    fi

    print_status "Verifying outputs with checker..."

    local check_errors=0
    local total_files=0

    # Find all .in files that have corresponding .out files
    for infile in data/*.in; do
        if [[ -f "$infile" ]]; then
            local basename=$(basename "$infile" .in)
            local outfile="data/$basename.out"

            if [[ -f "$outfile" ]]; then
                total_files=$((total_files + 1))
                print_status "Checking $basename.in/out pair..."

                # Use the same output as both participant and jury output
                if timeout 10s ./checker "$infile" "$outfile" "$outfile" 2>/dev/null; then
                    print_success "✓ $basename passed checker"
                else
                    local checker_result=$?
                    print_error "✗ $basename failed checker (exit code: $checker_result)"
                    check_errors=$((check_errors + 1))
                fi
            fi
        fi
    done

    if [[ $total_files -eq 0 ]]; then
        print_warning "No input/output pairs found for checking"
    elif [[ $check_errors -eq 0 ]]; then
        print_success "All $total_files pairs passed checker verification"
    else
        print_error "$check_errors/$total_files pairs failed checker verification"
        return 1
    fi
}

# Clean up compiled files
cleanup() {
    print_status "Cleaning up compiled files..."
    local files_to_clean=("generator" "validator" "checker" "std" "std_debug" "std_fast")

    for file in "${files_to_clean[@]}"; do
        if [[ -f "$file" ]]; then
            rm -f "$file"
            print_status "Removed $file"
        fi
    done

    # Clean up Java class files
    if [[ -f "std.class" ]]; then
        rm -f "std.class"
        print_status "Removed std.class"
    fi

    # Clean up testlib.h if we copied it
    if [[ -f "testlib.h" ]]; then
        rm -f "testlib.h"
        print_status "Removed testlib.h"
    fi

    print_success "Cleanup completed"
}

# Show summary
show_summary() {
    print_success "Pipeline completed successfully!"

    echo
    print_status "Generated files summary:"

    # Count files
    local in_files=$(find data -name "*.in" 2>/dev/null | wc -l)
    local out_files=$(find data -name "*.out" 2>/dev/null | wc -l)

    echo "  Input files:  $in_files"
    echo "  Output files: $out_files"

    # List files
    if [[ $in_files -gt 0 ]]; then
        echo
        print_status "Input files:"
        find data -name "*.in" -exec basename {} \; | sort | sed 's/^/    /'
    fi

    if [[ $out_files -gt 0 ]]; then
        echo
        print_status "Output files:"
        find data -name "*.out" -exec basename {} \; | sort | sed 's/^/    /'
    fi

    echo
    print_status "You can now use these test files for contest submission."
}

# Main execution
main() {
    # If a directory argument is provided, change to that directory
    if [[ -n "$1" ]]; then
        if [[ -d "$1" ]]; then
            print_status "Changing to directory: $1"
            cd "$1" || {
                print_error "Failed to change to directory: $1"
                exit 1
            }
        else
            print_error "Directory not found: $1"
            exit 1
        fi
    fi

    echo
    print_status "=== Algorithm Contest Problem Pipeline ==="
    print_status "Current directory: $(pwd)"
    echo

    # Check prerequisites
    check_problem_directory
    check_testlib

    # Execute pipeline
    compile_all
    generate_data
    validate_data
    generate_outputs
    verify_samples_with_debug  # Verify samples with bounds-checked debug build
    check_outputs
    show_summary

    # Ask about cleanup (skip if non-interactive or -y flag)
    if [[ -t 0 ]]; then
        echo
        read -p "Clean up compiled files? (y/N): " -n 1 -r
        echo
        if [[ $REPLY =~ ^[Yy]$ ]]; then
            cleanup
        fi
    else
        print_status "Non-interactive mode detected, skipping cleanup"
    fi

    print_success "Pipeline execution completed!"
}

# Handle script interruption
trap 'print_error "Pipeline interrupted"; cleanup; exit 1' INT TERM

# Run main function
main "$@"