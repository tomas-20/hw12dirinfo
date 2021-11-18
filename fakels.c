#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int get_file_size(char *file_name) {
  struct stat file_stats;
  stat(file_name, &file_stats);
  return file_stats.st_size;
}

int get_dir_size(DIR *dir, char *dir_name) {
  int dir_size = 0;
  chdir(dir_name);
  rewinddir(dir);
  for (struct dirent *entry; (entry = readdir(dir));) {
    int file_type = entry->d_type;
    if (file_type == DT_REG) {
      char *file_name = entry->d_name;
      int file_size = get_file_size(file_name);
      dir_size += file_size;
    }
  }
  chdir("..");
  return dir_size;
}

void show_files(DIR *dir, int type) {
  rewinddir(dir);
  for (struct dirent *entry; (entry = readdir(dir));) {
    int file_type = entry->d_type;
    if (file_type == type) {
      char *file_name = entry->d_name;
      printf("  %s\n", file_name);
    }
  }
}

void fakels(char *dir_name) {
  DIR *dir = opendir(dir_name);
  printf("Directory size: %d\n", get_dir_size(dir, dir_name));
  printf("Directories:\n");
  show_files(dir, DT_DIR);
  printf("Regular files:\n");
  show_files(dir, DT_REG);
}

int main() {
  fakels("sandwich");
  return 0;
}
