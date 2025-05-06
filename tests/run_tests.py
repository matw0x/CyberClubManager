import subprocess
import sys
import filecmp
import os

try:
    separator_index = sys.argv.index('--')
except ValueError:
    print("Usage: python run_tests.py <expected_output_path> -- <cpp_executable> [cpp_args...]")
    print("Error: '--' separator not found in arguments.")
    sys.exit(1)

if separator_index < 2:
     print("Usage: python run_tests.py <expected_output_path> -- <cpp_executable> [cpp_args...]")
     print("Error: Missing expected_output_path or command after '--'.")
     sys.exit(1)

expected_output_path = sys.argv[1]
cpp_command_args = sys.argv[separator_index + 1:]

if not cpp_command_args:
    print("Error: No command provided after '--'.")
    sys.exit(1)

executable_path = cpp_command_args[0]

print(f"Running command: {' '.join(cpp_command_args)}")
print(f"Expecting output from: {expected_output_path}")

actual_output_path = "actual_output.txt"

try:
    result = subprocess.run(cpp_command_args, capture_output=True, text=True, check=False, encoding='utf-8')

    with open(actual_output_path, 'w', encoding='utf-8') as f:
        f.write(result.stdout)

    if result.stderr:
        print("--- STDERR ---")
        print(result.stderr)
        print("--------------")

    actual_output_empty = not os.path.exists(actual_output_path) or os.path.getsize(actual_output_path) == 0
    expected_output_empty = not os.path.exists(expected_output_path) or os.path.getsize(expected_output_path) == 0

    match = False
    if actual_output_empty and expected_output_empty:
        match = True
    elif not actual_output_empty and not expected_output_empty:
        try:
            match = filecmp.cmp(actual_output_path, expected_output_path, shallow=False)
        except FileNotFoundError:
             print(f"Error: Expected output file not found: {expected_output_path}")
             match = False

    if match:
        print("Test PASSED: Output matches expected.")
        sys.exit(0)
    else:
        print("Test FAILED: Output mismatch.")
        print("--- ACTUAL OUTPUT ---")

        if os.path.exists(actual_output_path):
            with open(actual_output_path, 'r', encoding='utf-8') as f:
                 print(f.read())
        else:
            print("<No actual output file generated>")
        print("--------------------")
        print("--- EXPECTED OUTPUT ---")

        if os.path.exists(expected_output_path):
            with open(expected_output_path, 'r', encoding='utf-8') as f:
                 print(f.read())
        else:
             print("<No expected output file found>")
        print("-----------------------")
        sys.exit(1)

except FileNotFoundError:
    print(f"Test FAILED: Executable not found at {executable_path}")
    sys.exit(1)
except Exception as e:
    print(f"Test FAILED: An unexpected error occurred - {e}")
    import traceback
    traceback.print_exc()
    sys.exit(1)
finally:
    if os.path.exists(actual_output_path):
        try:
            os.remove(actual_output_path)
        except Exception as e:
            print(f"Warning: Failed to remove temporary file {actual_output_path}: {e}")