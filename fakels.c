#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

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
  fakels("sandwich");
}
