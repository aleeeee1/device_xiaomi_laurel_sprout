def sort_elements(file_path, element_key):
    with open(file_path, "r") as file:
        lines = file.readlines()

    in_override_block = False
    collected_overrides = set()
    updated_lines = []

    for line in lines:
        if in_override_block:
            cleaned_line = line.replace("\\", "").strip()
            collected_overrides.add(cleaned_line)
            if "\\" not in line:
                in_override_block = False
                updated_lines.append("    " + " \\\n    ".join(sorted(collected_overrides, key=str.casefold)) + "\n")
                collected_overrides.clear()
            continue

        updated_lines.append(line)
        if element_key in line:
            in_override_block = True

    with open(file_path, "w") as file:
        file.writelines(updated_lines)

sort_elements("Android.mk", "LOCAL_OVERRIDES_PACKAGES")