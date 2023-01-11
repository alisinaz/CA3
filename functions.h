#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <string.h>
/*each account has a "first post pointer" cuz we save posts in a seperate linked list for every user... */


typedef struct posts  //defining structure for posts
{
    int id;
    int likes;
    char* text;
    struct accounts** likers;
    struct posts *next;
}pp;

typedef struct accounts  //defining structure for accounts
{
    char* username;
    char* password;
    pp* first_post_node;
    struct accounts* next;
} acc;

/////////////////////////////////////////////////////////////////

//this function calculate the size of input(not in bytes)...

int size_of(char* input){    
    int i=0;
    while(input[i]!='\0'){
        i++;
    }
    return i+1;
}
/////////////////////////////////////////////////////////////////

//the next three functions return first word , second word and third word(its actually the rest of string) of a string called input...


char* first_word(char* input){     
    if(input[0] == '\n' || input[0] == '\0' || input == NULL){
        return NULL;
    }
    int i=0;
    char* str=(char*)malloc((i+1)*sizeof(char));
    while(input[i]!=' ' && input[i]!='\n'){
        str=(char*)realloc(str,(i+1)*sizeof(char));
        str[i]=input[i];
        i++;
    }
    str[i]='\0';
    return str;
}
/////////////////////////////////////////////////////////////////
char* second_word(char* input){
    int i=0;
    while(input[i]!=' ' && input[i]!='\n' && input[i]!='\0'){
        i++;
    }
    if(input[i] == '\n' || input[i] == '\0'){
        return NULL;
    }

    i++;
    int j=i;
    char* str=(char*)malloc((i-j+1)*sizeof(char));
    while(input[i]!=' ' && input[i]!='\n' && input[i]!='\0'){
        str=(char*)realloc(str,(i-j+1)*sizeof(char));
        str[i-j]=input[i];
        i++;
    }
    str[i-j]='\0';
    return str;
}
/////////////////////////////////////////////////////////////////
char* third_word(char* input){
    int i=0;
    while(input[i]!=' ' && input[i]!='\n' && input[i]!='\0'){
        i++;
    }
    if(input[i] == '\n' || input[i] == '\0'){
        return NULL;
    }
    i++;
    while(input[i]!=' ' && input[i]!='\n' && input[i]!='\0'){
        i++;
    }
    if(input[i] == '\n' || input[i] == '\0'){
        return NULL;
    }
    i++;
    int j=i;
    char* str=(char*)malloc((i-j+1)*sizeof(char));
    while(input[i]!='\n' && input[i]!='\0'){       // input[i]!=' ' && 
        str=(char*)realloc(str,(i-j+1)*sizeof(char));
        str[i-j]=input[i];
        i++;
    }
    str[i-j]='\0';
    return str;
}
/////////////////////////////////////////////////////////////////

//this function is getting input from user (1 by 1 chars...till we see an ENTER pressed)

char* get_input(){
    int i=0;
    char* input=(char*)malloc((i+1)*sizeof(char));
    input[i]=getchar();
    /*if(input[i] == '\n' || input[i] == '\0'){
        return NULL;
    }*/
    while(input[i]!='\n'){
        i++;
        input=(char*)realloc(input,(i+1)*sizeof(char));
        input[i]=getchar();
    }
    input[i]='\0';
    fflush(stdin);
    return input;
}
/////////////////////////////////////////////////////////////////

//this function returns the post's text (with out the word "post" at the beginning)

char* get_post(char* input){ 
    int i=0;
    while(input[i]!=' ' && input[i]!='\n' && input[i]!='\0'){
        i++;
    }
    i++;
    int j=i;
    char* str=(char*)malloc((i-j+1)*sizeof(char));
    while(input[i]!='\n' && input[i]!='\0'){
        str=(char*)realloc(str,(i-j+1)*sizeof(char));
        str[i-j]=input[i];
        i++;
    }
    str[i-j]='\0';
    return str;


}
//////////////////////////////////////////////////////////////////

// this function takes an string(input) , username of the new user and a password for new user as input and it vreated a new user (account) and returns it... 

acc* add_user(char* input ,char* name ,char* password){
    acc* new_user = (acc*)malloc(sizeof(acc));
    new_user->username = (char*)malloc(size_of(name)*sizeof(char));
    new_user->password = (char*)malloc(size_of(password)*sizeof(char));
    strcpy(new_user->username , name);
    strcpy(new_user->password , password);
    new_user->next = NULL;
    new_user->first_post_node = (pp*)malloc(sizeof(pp));
    new_user->first_post_node->next =NULL;
    new_user->first_post_node->id =0 ;
    return new_user;
}

///////////////////////////////////////////////////////////////////

/*this function takes first node (dummy) and a username to check if there is an account with that username ... it returns NULL if no such account exist or a pointer to that account otherwise*/ 

acc* name_check(acc* first_node , char* name){
    acc* node = first_node->next;
    while(node != NULL && strcmp(node->username , name) != 0){
        node = node->next;
    }
    return node;
}
////////////////////////////////////////////////////////////////////

/*this void function creates post for a specific account (node)*/

void add_post(acc* node , char* post_text){
    pp* cur_post_node = node->first_post_node;
    while(cur_post_node->next != NULL){
        cur_post_node = cur_post_node->next;
    }
    pp* new_post = (pp*)malloc(sizeof(pp));
    new_post->text = (char*)malloc(size_of(post_text)*sizeof(char));
    strcpy(new_post->text , post_text);
    new_post->id = (cur_post_node->id) + 1;
    new_post->likes = 0 ;
    cur_post_node->next = new_post;
    new_post->likers =(acc**)malloc(sizeof(acc*));
    new_post->likers[0] = NULL;
    new_post->next = NULL;
}
////////////////////////////////////////////////////////////////////

/*this void function removes post for a specific account (node) by searching for its Id...*/

void remove_post(acc* node , int id){
    pp* cur_posts_node = node->first_post_node->next;
    pp* per_node_post = node->first_post_node;
    while(cur_posts_node->id != id && cur_posts_node != NULL){
        cur_posts_node = cur_posts_node->next ;
        per_node_post = per_node_post->next ;
    }
    if(cur_posts_node == NULL){
        printf("invalid user or post id ...\n");
        return;
    }
    per_node_post->next = cur_posts_node->next ;
    free(cur_posts_node);
    printf("The post has been removed successfully !\n");


}

////////////////////////////////////////////////////////////////////

//this function prints all posts from a user (node)...

void print_posts(acc* node){
    pp* cur_post = node->first_post_node;
    cur_post = cur_post->next;
    if(cur_post == NULL){
        printf("no posts yet ... \n");
        return;
    }
    while(cur_post != NULL){
        printf("post : %s   id : %d     likes : %d\n",cur_post->text , cur_post->id , cur_post->likes);
        cur_post = cur_post->next;
    }
}
///////////////////////////////////////////////////////////////////

//it prints information of a user...

void print_info(acc* node){
    printf("Username  : %s\nPassword : %s\n",node->username , node->password);
    print_posts(node);
}
///////////////////////////////////////////////////////////////////

/*this function takes a string as input which is supposed to be only numbers and it returns that number as an int or if input has anything other than numbers it returns 0 ...*/

int char_to_int(char* str_num){
    if(str_num == NULL){
        return 0;
    }
    int size = size_of(str_num) -1;
    int s = 0;
    int powerof10 = 1;
    for(int i = size ; i>0 ; i--){
        int x = str_num[i-1] - '0';
        if(x>9 || x<0){
            return 0;
        }
        s = s + (x * powerof10);
        powerof10 = powerof10 * 10;
    }
    return s;
    
}
/////////////////////////////////////////////////////////////////////////

//this function is to like a user's post by searching for its Id...
void like(acc* liker_node , acc* user , int id){
    pp* post_node = user->first_post_node->next;
    while(post_node != NULL && post_node->id != id){
        post_node = post_node->next;
    }
    if(post_node == NULL){
        printf("This user name hasn't a post with that ID...\n");
        return;
    }
    for(int i = 0 ; i<post_node->likes ; i++){
        if(post_node->likers[i] == liker_node){
            printf("You liked this post before...\n");
            return;
        }
    }
    printf("You liked %s 's post !\n" , user->username);
    post_node->likes ++;
    post_node->likers = (acc**)realloc(post_node->likers , (post_node->likes + 1)*sizeof(acc*));
    post_node->likers[post_node->likes - 1] = liker_node;
    post_node->likers[post_node->likes] = NULL;

}
/////////////////////////////////////////////////////////////////////////
int num_of_posts(acc *node){
    pp* cur_post_node = node->first_post_node->next;
    int counter = 0;
    while(cur_post_node != NULL){
        counter++;
        cur_post_node = cur_post_node->next;
    }
    return counter;
}
///////////////////////////////////////////////////////////////////////////

void write_users_in_files(acc *first_node){
    FILE *ac = fopen("accounts.txt" , "w");
    acc *cur_node = first_node->next;
    while(cur_node != NULL){
        fprintf(ac , "%s %s %d\n" , cur_node->username , cur_node->password , num_of_posts(cur_node));
        cur_node = cur_node->next;
    }
    fclose(ac);
}

////////////////////////////////////////////////////////////////////////
void write_posts_in_file(acc *first_node){
    FILE *p = fopen("post.txt" , "w");
    acc *cur_node = first_node->next;
    while(cur_node != NULL){
        pp *post_node = cur_node->first_post_node->next;
        while(post_node != NULL){
            fprintf(p,"%s   %s  %d\n" ,post_node->text , cur_node->username , post_node->likes);
            post_node = post_node->next;
        }
        cur_node = cur_node->next;
    }
    fclose(p);
}

