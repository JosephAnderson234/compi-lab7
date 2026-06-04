import os
import subprocess
import shutil

# Archivos c++
programa = ["main.cpp", "scanner.cpp", "token.cpp", "parser.cpp", "ast.cpp", "visitor.cpp","semantic_types.h",
"TypeChecker.cpp"]

# Compilar
compile = ["g++"] + programa
print("Compilando:", " ".join(compile))
result = subprocess.run(compile, capture_output=True, text=True)

if result.returncode != 0:
    print("Error en compilación:\n", result.stderr)
    exit(1)

print("Compilación exitosa")

# Ejecutar
input_dir = "inputs"
output_dir = "outputs"
os.makedirs(output_dir, exist_ok=True)

input_files = sorted([f for f in os.listdir(input_dir) if f.startswith("input") and f.endswith(".txt")])

for filename in input_files:
    filepath = os.path.join(input_dir, filename)
    print(f"Ejecutando {filename}")
    run_cmd = ["./a.out", filepath]
    result = subprocess.run(run_cmd, capture_output=True, text=True)

    base = filename.replace(".txt", "").replace("input", "")
    output_file = os.path.join(output_dir, f"output{base}.txt")
    with open(output_file, "w", encoding="utf-8") as f:
        f.write("=== STDOUT ===\n")
        f.write(result.stdout)
        f.write("\n=== STDERR ===\n")
        f.write(result.stderr)

    tokens_file = os.path.join(input_dir, f"input{base}_tokens.txt")
    ast_file = "ast.dot"

    if os.path.isfile(tokens_file):
        dest_tokens = os.path.join(output_dir, f"tokens_{base}.txt")
        shutil.move(tokens_file, dest_tokens)

    if os.path.isfile(ast_file):
        dest_ast = os.path.join(output_dir, f"ast_{base}.dot")
        shutil.move(ast_file, dest_ast)

        output_img = os.path.join(output_dir, f"ast_{base}.png")
        dot_cmd = ["dot", "-Tpng", dest_ast, "-o", output_img]
        subprocess.run(dot_cmd, capture_output=True, text=True)
