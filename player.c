

/* BERKANT TUGBERK DEMIRTAS 2315232 */

/* INPUT AND OUTPUT FILES BEGIN WITH PLAYERS AND STATISTICS. I SKIPPED THE FIRST LINE */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct player{ /* INPUT FILE STRUCT */

    char name[20];
    char surname[20];
    int goals;
    int assists;
    int red_cards;
    int pass_success;
};

struct statics{ /* OUTPUT FILE STRUCT */
    char name[20];
    char surname[20];
    int pass_success;
    int pass_rate;

};

int Load_Statistics_Table(char *, struct player **);
void Display_Statistics_Table(struct player *, int);
int Search(struct player *, int, char []);
void No_red_card(struct player *,int, char[]);
void Player_with_Highest_Goal(struct player *,int, char[]);
void Store_statistics (struct statics **,struct player *, int,char *);


int main(int argc, char *argv[]){

    struct player *statistics_table; // INPUT FILE ARRAY
    struct statics *output; // OUTPUT FILE ARRAY */
    int size,position; // SIZE FOR INPUT ARRAY, POSITION FOR SEARCH FUNC
    char answer[20]; // FOR USER INPUT

    if(strcmp(argv[1],"player.txt") != 0) //CHECKS INPUT FILE VALID OR NOT
            printf("Please try again.");
    else{
         printf("\n");printf("Score records file has been succesfully loaded!\n");printf("Following records have been loaded!\n");

        printf("Player      G  A  RC  PS\n");
        size=Load_Statistics_Table(argv[1],&statistics_table); // RUN THE FUNCTION GETS THE SIZE
        Display_Statistics_Table(statistics_table,size); // RUN THE FUNC

        printf("Enter the name of the player (Exit  X, No Red Card  NR, Player with Highest Goal  G):");
        scanf("%s",answer);

        while(answer[0]!='X' && answer[0]!='x'){ // RUNS TILL USER ENTERS 'X'

            if (strlen(answer)>=3){ // IF INPUT HAS MORE THAN 3 CHAR IT CONSIDERED AS NAME INPUT
                position=Search(statistics_table,size,answer); //RUNS THE SEARCH FUNC GETS THE POSITION
                if(position!=-1){ // IF IT'S MATCHING;

                    printf("%s %s has %d goals, %d assists, %d red cards, %d successful passes. \n",statistics_table[position].name,statistics_table[position].surname,statistics_table[position].goals,statistics_table[position].assists,statistics_table[position].red_cards,statistics_table[position].pass_success);
                }
                else // IF IT'S NOT MATCHING
                    printf("That player is unknown! Please try again!\n");

            }
            else if(answer[0]=='N' && answer[1]=='R' ) // STATEMENT FOR RUNNING NO RED CARD FUNC
                No_red_card(statistics_table,size,answer);
            else if(answer[0]=='G')// STATEMENT FOR RUNNING HIGHEST GOAL
                Player_with_Highest_Goal(statistics_table,size,answer);

            fflush(stdin); //RESET THE BUFFER
            printf("\nEnter the name of the player (Exit  X, No Red Card  NR, Player with Highest Goal  G):");
            scanf("%s",answer);

        }
        printf("Storing statistics.txt on exit with the following data:\n");

        Store_statistics(&output,statistics_table,size,argv[2]); // RUNS THE FUNC


    }

   return 0;
}

int Load_Statistics_Table(char argv[10],struct player **statistics_table){

    FILE *infile;
    int counter=0;
    int i=0;

   infile=fopen(argv,"r"); //OPENS FILE AND CHECKS IF IT'S EXIT
        if(infile== NULL)
            printf("The file is null.");

        while(!feof(infile)){ //COUNTS THE CHAR FOR SIZE OF ARRAY
            fgetc(infile);
            counter+=1;
        }
        fclose(infile);

        infile=fopen(argv,"r");
        if(infile==NULL)
            printf("NULL");


        *statistics_table= (struct player *)  malloc(sizeof(struct player )*counter); //DYNAMIC ALLOCATION

        if(*statistics_table==NULL)
            printf("NULL");


           while(!feof(infile)) // FILLS THE ARRAY FROM FILE
        {
            fscanf(infile,"%s",(*statistics_table)[i].name);
            fscanf(infile,"%s",(*statistics_table)[i].surname);
            fscanf(infile,"%d",&(*statistics_table)[i].goals);
            fscanf(infile,"%d",&(*statistics_table)[i].assists);
            fscanf(infile,"%d",&(*statistics_table)[i].red_cards);
            fscanf(infile,"%d",&(*statistics_table)[i].pass_success);

            i++;
        }

            int size=i; // SIZE OF ARRAYS

        fclose(infile);

        return size;

}
void Display_Statistics_Table(struct player *statistics_table, int size){
    int i;
    for(i=0;i<size;i++) // DISPLAYS THE ARRAY
            {
                printf("%s %s %d %d %d %d \n",statistics_table[i].name,statistics_table[i].surname,statistics_table[i].goals,statistics_table[i].assists,statistics_table[i].red_cards,statistics_table[i].pass_success);
            }


    }

int Search(struct player *statistics_table, int size, char name[20]){

    int matched=0; //MATCH VARIABLE
    int i;
    int position; // FOR POSITION

    for(i=0;i<size; i++){
        if(strcmp(statistics_table[i].name,name)==0){ //CHECKS IF IT'S MATCHED
            matched=1;
            position=i; // MATCHED POSITION
        }

    }

    if(matched==1) // IF IT'S MATCHED
        return position;
    else
        return -1;

}
void No_red_card(struct player *statistics_table,int size, char name[2]){
    int i;

    for(i=0;i<size;i++){
        if(statistics_table[i].red_cards==0) // CHECKS PLAYER THAT HAVE NOT RED CARD
            printf("%s %s, ",statistics_table[i].name,statistics_table[i].surname); // PRINT THOSE PLAYERS
    }

}

void Player_with_Highest_Goal(struct player *statistics_table,int size, char name[1]){

 int highest_goal = statistics_table[0].goals; // INITIALIZE FOR HIGHEST GOAL COMPARISON
 int position; // TO KEEP POSITION
 int i;

    for(i=0;i<size;i++){
        if(statistics_table[i].goals>highest_goal){ // DETERMINES THE HIGHEST GOAL
            highest_goal=statistics_table[i].goals;
            position=i;
        }
    }
    printf("%s %s ! He has %d goals.",statistics_table[position].name,statistics_table[position].surname,highest_goal); // PRINTS IT

}

void Store_statistics (struct statics **output,struct player *statistics_table, int size,char output_txt[15]){
    FILE *infile;
    FILE *outfile;

    int i=0,counter=0;

    int pass_success_rate[size]; //TEMPORARY ARRAY FOR CALCULATING SUCCESS RATE

    infile=fopen("player.txt","r");
        if(infile== NULL)
            printf("The file is null.");

        while(!feof(infile)){ // COUNTS CHAR FOR ALLOCATION
            fgetc(infile);
            counter+=1;
        }
        fclose(infile);

    *output= (struct statics *)  malloc(sizeof(struct statics )*counter); // DYNAMIC ALLOCATION

    for(i=0;i<size;i++){
        strcpy((*output)[i].name, statistics_table[i].name); // COPIES THE NAME
        strcpy((*output)[i].surname, statistics_table[i].surname); // COPIES THE SURNAME

        (*output)[i].pass_success= statistics_table[i].pass_success; //COPIES THE PASS SUCCESS
    }

    for(i=0;i<size;i++){
       pass_success_rate[i]=statistics_table[i].pass_success*100/20; // CALCULATE SUCCESS RATE AND ASSIGN IT TO TEMPORARY ARRAY
        (*output)[i].pass_rate=pass_success_rate[i]; // ASSIGN TEMP ARRAY TO STRUCT ARRAY
    }

    printf("Player      PS PassSuccessRate \n");
   for(i=0;i<size;i++){ //DISPLAY OUTPUT
       printf("%s %s %d %d \n",(*output)[i].name,(*output)[i].surname,(*output)[i].pass_success,(*output)[i].pass_rate);

    }

    outfile= fopen(output_txt,"w");

    for(i=0;i<size;i++){ // WRITES TO FILE
       fprintf(outfile,"%s %s %d %d \n",(*output)[i].name,(*output)[i].surname,(*output)[i].pass_success,(*output)[i].pass_rate);
    }

    fclose(outfile);


};






















