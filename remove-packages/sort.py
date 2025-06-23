def sort_elements(file_path, element_key):
    with open(file_path, "r") as file:
        lines = file.readlines()
    
    tab =  "    " * 2

    in_override_block = False
    collected_overrides = set()
    updated_lines = []

    for line in lines:
        if in_override_block:
            if "]" in line:
                in_override_block = False
                updated_lines.append(tab
                                     + f",\n{tab}".join(sorted(collected_overrides, key=str.casefold))
                                     + ",\n")
                print(collected_overrides)
                collected_overrides.clear()
            
            else:
                cleaned_line = line.replace(",", "").strip()
                collected_overrides.add(cleaned_line)
                continue

        updated_lines.append(line)
        if element_key in line:
            in_override_block = True

    with open(file_path, "w") as file:
        file.writelines(updated_lines)

sort_elements("Android.bp", "overrides")