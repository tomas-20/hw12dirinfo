#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

int get_size(char *filename) {
  struct stat filestats;
  stat(filename, &filestats);
  return filestats.st_size;
}

void fakels(char *dirname) {
  DIR *dir = opendir(dirname);
  for (struct dirent *entry; (entry = readdir(dir));) {
    char *filename = entry->d_name;
    printf("%s ", filename);
  }
  closedir(dir);
  printf("\n");
}

int main() {
  //fakels("sandwich");
  //dirsize("sandwich");
  printf("%d\n", get_size("wabaloo"));
  printf("%d\n", get_size("milanesa"));
  printf("%d\n", get_size("sandwich/milanesa"));
  return 0;
}
