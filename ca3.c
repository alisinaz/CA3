#include "functions.h"
/*Overall concept :
First we define structures for saving posts and users and then we defined some functions which is used in our code (see 'functions.h')
After that we define commands which have been defined in the project 1 by 1 ... (you can understand every thing clearly by reading codes and comments next to them :)) */
/*note : read 'functions.h' first to have a better understand of this code...*/

void main(){
    system("cls");
    printf("note : type shutdown to close the app...\n");
    acc* first_node =(acc*)malloc(sizeof(acc)); //creating dummy node for accounts...
    first_node->next = NULL;
    first_node->first_post_node = NULL;
    acc* node = first_node; //node is always the last user created...
    while(1){ 
        //system("cls");
        printf("what do you want to do now ?  \n");
        char* input = get_input();//getting commands from user...
        if(first_word(input) == NULL){
            printf("enter a valid input please !\n");
        }
        else if(strcmp(first_word(input) , "signup")==0){
            if(name_check(first_node , second_word(input))==NULL && second_word(input) != NULL && third_word(input) != NULL && strcmp(second_word(input),"signup")!=0 && strcmp(second_word(input),"login")!=0 && strcmp(second_word(input),"info")!=0 && strcmp(second_word(input),"find_user")!=0 && strcmp(second_word(input),"like")!=0 && strcmp(second_word(input),"post")!=0 && strcmp(second_word(input),"delete")!=0 && strcmp(second_word(input),"logout")!=0){
                node->next = add_user(input , second_word(input) ,third_word(input));
                node = node->next;
                node->next = NULL;
                printf("signup was successful !\n");
                printf("username : %s\npassword : %s\n",node->username , node->password);
                write_users_in_files(first_node);
            }
            else{
                printf("this username has been taken or invalid input type !\n");
            }
        }//end of signup



        else if(strcmp(first_word(input) , "login")==0){
            acc* temp_node = name_check(first_node , second_word(input));
            if(temp_node!= NULL && strcmp(temp_node->password , third_word(input)) == 0 ){
                printf("you are loggedin...\n");
                //now user is logged in...
                while(1){
                    printf("what to do next ?\n");
                    char* input_in = get_input(); //getting commands from user while loggedin...
                    if(first_word(input) == NULL){
                        printf("enter a valid input please !\n");
                    }
                    else if(strcmp(input_in , "logout") == 0){
                        printf("logout successful !\n");
                        break;
                    }//end of logout

                    else if(strcmp(first_word(input_in) , "post")==0){
                        char* post_txt = get_post(input_in);
                        add_post(temp_node , post_txt);
                        write_posts_in_file(first_node);
                        write_users_in_files(first_node);
                    }//end of post

                    else if(strcmp(input_in , "info") == 0){
                        print_info(temp_node);
                    }//end of info

                    else if(strcmp(first_word(input_in) , "like") == 0){
                        int id = char_to_int(third_word(input_in));
                        acc* user = name_check(first_node,second_word(input_in));
                        if(user != NULL && id > 0){
                            like(temp_node , user , id);
                            write_posts_in_file(first_node);
                        }
                        else{
                            printf("Invalid username ...");
                        }
                    }//end of like

                    else if(strcmp(first_word(input_in) , "delete")==0 ){
                        int id = char_to_int(second_word(input_in));
                        remove_post(temp_node , id);
                        write_posts_in_file(first_node);
                        write_users_in_files(first_node);
                        
                    }//end of delete post

                    else if(strcmp(first_word(input_in) , "find_user") == 0){
                        if(name_check(first_node , second_word(input_in)) == NULL || third_word(input_in) != NULL || second_word(input_in) == NULL){
                            printf("Invalid user...!\n");
                        }     
                        
                        else{
                            print_info(name_check(first_node , second_word(input_in)));
                        }
                    }//end of user search

                    else{
                        printf("Enter a valid input, please or you can logout by typing 'logout' !\n");
                    }
                    fflush(stdin);
                    free(input_in);
                }
            }
            else{
                printf("username or password incorrect !\n");
            }
        }//end of login

        else if(strcmp(first_word(input) , "shutdown") == 0){ //if user wants to close the app 
            break;
        }

        
        else if(strcmp(first_word(input) , "logout")==0 || strcmp(first_word(input) , "info")==0 || strcmp(first_word(input) , "like")==0 || strcmp(first_word(input) , "find_user")==0 || strcmp(first_word(input) , "logout")==0 || strcmp(first_word(input) , "delete")==0 || strcmp(first_word(input) , "post")==0 ||strcmp(first_word(input) , "find_user")==0 ){
                printf("You need to login first !\n"); //if they enter a valid command but they are not loggedin...
        }
        else{
            printf("enter a valid input please !\n"); // if they enter invalid command
        }
        fflush(stdin);
        free(input);
    }
}