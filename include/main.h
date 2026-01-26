#ifndef LOOPOVER_MAIN_H
#define LOOPOVER_MAIN_H

constexpr char LOOPOVER_PREPARE_TEXT[] = "Preparing the state...";
constexpr char LOOPOVER_LOAD_TEXT[] = "Loading the state...";
constexpr char LOOPOVER_MODIFY_TEXT[] = "Modifying the state...";

constexpr char LOOPOVER_PREPARE_ERROR[] = "Failed to prepare the state :(";
constexpr char LOOPOVER_LOAD_ERROR[] = "Failed to load the state :(";
constexpr char LOOPOVER_MODIFY_ERROR[] = "Failed to modify the state :(";

constexpr char LOOPOVER_SUCCESS_TEXT[] = "Modified the state successfully!";
constexpr char LOOPOVER_SUCCESS_BOTTLE[] = "Patched the bottles successfully!";
constexpr char LOOPOVER_BOTTLE_ERROR[] = "Failed patching the bottle :(";

[[nodiscard]] bool get_confirmation(void);

[[nodiscard]] bool handle_modify(const char *path);

int main(void);

#endif
