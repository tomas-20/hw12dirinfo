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
  for (struct dirent *file; (file = readdir(dir));) {
    if (file->d_type == DT_REG) {
      dir_size += get_file_size(file->d_name);
    }
  }
  chdir("..");
  return dir_size;
}

void show_files(DIR *dir, int type) {
  rewinddir(dir);
  for (struct dirent *file; (file = readdir(dir));) {
    if (file->d_type == type) {
      printf("  %s\n", file->d_name);
    }
  }
}

void fakels(char *dir_name) {
  DIR *dir = opendir(dir_name);
  if (dir) {
    printf("Directory size: %d\n", get_dir_size(dir, dir_name));
    printf("Directories:\n");
    show_files(dir, DT_DIR);
    printf("Regular files:\n");
    show_files(dir, DT_REG);
    closedir(dir);
  }
  else {
    printf("Directory does not exist\n");
  }
}

int main() {
  fakels("sandwich");
  return 0;
}
