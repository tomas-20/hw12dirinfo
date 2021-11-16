#include <dirent.h>
#include <stdio.h>

void fakels(char *dirname) {
  DIR *dir = opendir(dirname);
  for (struct dirent *entry = readdir(dir); entry; entry = readdir(dir)) {
    char *filename = entry->d_name;
    printf("%s ", filename);
  }
  printf("\n");
}

int main() {
  fakels("sandwich");
  return 0;
}
