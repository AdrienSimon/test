#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

/* #include <sys/dir.h> */

int traitementStat(char* path){
    int rep;
    
    /* la structure "stat" permet de récupérer les informations contenues dans
     les entêtes (i-noeud) de fichier. Elle se trouve dans le fichier
     "/usr/include/bits/stat.h"
     struct stat {
     unsigned short st_dev;   // identifiant du périphérique contenant le fichier
     unsigned short __pad1;
     unsigned long st_ino;    // i-noeud associé au fichier.
     unsigned short st_mode;  // mode du fichier (type et droit d'accès).
     unsigned short st_nlink; // nombre de liens absolus vers le fichier.
     unsigned short st_uid;   // identifiant de l'utilisateur proprietaire
     unsigned short st_gid;   // identifiant du groupe
     ...
     unsigned long st_size;   // taille du fichier en octets
     unsigned long st_blksize;// taille des blocs sur le peripherique
     unsigned long st_blocks; // nombre de blocs alloues
     __time_t st_atime;       // date du dernier accès.
     __time_t st_mtime;       // date de la dernière modification
     __time_t st_ctime;       // date du dernier changement de status
     };
     */
    struct stat st;
    /* recuperation des infos du i_noeud par stat */
    rep = stat(path,&st);
    
    if(rep == 0) {
        printf("%s : ino = %d\ttaille = %d\t",path,st.st_ino,st.st_size);
        if(S_ISDIR(st.st_mode)) printf(" DIRECTORY ");
        if(S_ISREG(st.st_mode)) printf(" FICHIER ");
        if(S_ISLNK(st.st_mode)) printf(" LIEN ");
        printf("owner = %d\tgrpe = %d\n",st.st_uid,st.st_gid);
        
        if(S_ISDIR(st.st_mode)) return 0;
        return -1;
    }
    else {
        perror("erreur de stat");
        exit(2);
    }
    
    
    
}


void traitementDir(char * path){
    /* la structure DIR permet de récupérer des informations sur un répertoire */
    DIR* dir;
    /* la structure "dirent" contient des informations sur un élément du
     répertoire (le détail d'une entrée de répertoire, c'est-à-dire le
     "i-noeud" du fichier et son nom). La structure "dirent" se trouve dans
     le fichier "/usr/include/bits/dirent.h".
     
     struct dirent {
     #ifndef __USE_FILE_OFFSET64
     __ino_t d_ino;
     __off_t d_off;
     #else
     __ino64_t d_ino;
     __off64_t d_off;
     #endif
     ...
     char d_name[256];
     }; */
    struct dirent* dirdata;
    
    /* ouverture du repertoire et controle d'existence */
    dir = opendir(path);
    if(dir == NULL) {
        perror("erreur opendir");
        exit(0);
    }
    /* lecture des donnees du repertoire */
    while((dirdata = readdir(dir)) != NULL) {
        printf("%s : N ino = %d\tNom = %s\n",path,dirdata->d_ino,dirdata->d_name);
        
        /** path/dirdata->d_name*/
        char* pathfils = malloc(strlen(path)+strlen("/")+strlen(dirdata->d_name));
        
        
        
        
        strcpy(pathfils,path);
        strcpy(pathfils+strlen(path),"/");
        strcpy(pathfils+strlen(path)+strlen("/"),dirdata->d_name);
        //printf(" Fils **%s**\n",pathfils);
        int isDir=traitementStat(pathfils);
        if(isDir==0) {
            if(strlen(".")==strlen(dirdata->d_name) && dirdata->d_name[0]=='.')
                    {}
            else if (strlen("..")==strlen(dirdata->d_name) && dirdata->d_name[0]=='.' && dirdata->d_name[1]=='.'){}
            else {traitementDir(pathfils);}
        }
    }
    /* fermeture du repertoire ouvert */
    closedir(dir);
}




int main(int argc, char *argv[]) {

  char* path;
  /* controle des parametres d'appel */
  if(argc != 2) {
	 printf("erreur de syntaxe d'appel.\n");
	 exit(1);
  }
  /* recuperation du nom du repertoire */
  path = (char*)malloc(strlen(argv[1]) +1);
  strcpy(path,argv[1]);
 
  traitementStat(path);
  traitementDir(path);
 
    
  /* liberation memoire */
  free(path);
 
}
