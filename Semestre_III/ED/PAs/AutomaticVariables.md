What does $<, $^ and $@ do?

Great question! These are **automatic variables** in `make` that help you write rules more concisely.

Here’s what each one does:

- **`$<`** → the **first** prerequisite (dependency)  
  - Example: in `$(OBJ_DIR)/pa2.o: $(SRC_DIR)/pa2.c`, `$<` is `src/pa2.c`

- **`$^`** → **all** prerequisites, space-separated  
  - Example: in `pa2.out: pa2.o graph.o`, `$^` is `pa2.o graph.o`

- **`$@`** → the **target** of the rule  
  - Example: in `$(OBJ_DIR)/pa2.o: ...`, `$@` is `obj/pa2.o`

### Summary table:

| Variable | Meaning                     | Example                    |
|----------|-----------------------------|----------------------------|
| `$@`     | Target                      | `obj/pa2.o`                |
| `$<`     | First prerequisite          | `src/pa2.c`                |
| `$^`     | All prerequisites           | `obj/pa2.o obj/graph.o`    |

These help keep your `Makefile` clean and avoid repeating file names.

Want a visual example of how they all expand?