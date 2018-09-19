/***********************************************************************************

 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 	COMPRO2   ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
 - - - - - - - - - - - - -Machine Project (MP) Phase 1- - - - - - - - - - - - - - -
- - - - - - - - - - - - - - - EDITOR JEOPARDY GAME - - - - - - - - - - - - - - - - -
* * * Members: * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
- - ->		Fernandez, Ma. Lourdes M. - -11612096		<- - - - - - - - - - - - - -
		
***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
typedef char string10[11];
typedef char string20[21];
typedef char string50[51];


typedef struct questionTag{
    string50 	question,
        	 	answer  ;
    int         val     ;
}questionType;

typedef struct categoryTag{
    string20        categoryName; 
    questionType    questions[6];  
}categoryType;
 
typedef struct FJTag{
	string50	    FJquestion  ,
				    FJanswer    ;
}FJType;

typedef struct gameTag{
	string10	    gameName    ;
	FJType			FJeopardy   ;
	categoryType    category[5] ;
	int				numCat		;  	
	struct gameTag *pNext       ;
	
}gameType;

typedef gameType *ptrGame ;

void phaseOneMenu(ptrGame pGames);
void viewGame(gameType *pGames);

/*
	PHASE ONE FUNCTIONS - CATEGORY THING
*/

/*
	Function AddCategory allows the user to add a new category to the game, then letting
	the user to add up until 5 categories. Each category will have the name, questions,
	answers, and points
*/
void 
AddCategory(ptrGame pGames)
{
	printf("\nSELECTED: ADD CATEGORY \n\n");
	printf("-----------------------------------------------------------");
	printf("\nNumber of categories is %d", pGames->numCat);
	int value[6] = {100, 200, 300, 400, 500, 1000};   
	int i, valid=1;
	string10 categoryName;
	if(pGames->numCat == 5){
	
		printf("\n**You already have 5 Categories**");
		return;
	}
	
	if(pGames->numCat < 6)
	{
	do
	{
		printf("\nName of Category : ");
		gets(categoryName);
		
		while (i<pGames->numCat && valid == 0){
			if(strcasecmp(categoryName, pGames->category[i].categoryName) == 0 )
				valid = 0;
			i++;
		}
		if(valid == 0)
			printf("ERROR: Category Already Exists");

			
	}while(valid == 0);
	
	strcpy(pGames->category[pGames->numCat].categoryName,categoryName);
	printf("\n-----------------------------------------------------------");
	for(i=0; i<=5; i++)
    {
		printf("\nPoints: %d ", value[i]);
		pGames->category[pGames->numCat].questions[i].val = value[i];
		
		printf("\nEnter Question %d :", i+1);
		fgets(pGames->category[pGames->numCat].questions[i].question, 51, stdin);
		
		printf("\nQuestion Answer: ");
		fgets(pGames->category[pGames->numCat].questions[i].answer, 51, stdin);
		
		printf("\n-----------------------------------------------------------");
	}
	pGames->numCat += + 1;
	}
	else 
		printf("\nERROR: The Limit of Categories[5] is Reached");

	printf("\n");
	system("pause");
}

/*
	User will input a category name and that category will be deleted from the entire
	category structure, if not found then it will report that it couldn't be found.
*/
void
DeleteCategory(ptrGame pGames)
{
	printf("\nSELECTED: DELETE CATEGORY \n\n");
	printf("-----------------------------------------------------------");
	int i,curr;
	string50 input;
	if(pGames->numCat>0)
	{
	printf("\nEnter Category name to be Deleted: ");
	gets(input);
	fflush(stdin);
	for(i=0;i<pGames->numCat;i++)
	{
		curr = i;
		if(strcasecmp(pGames->category[pGames->numCat].categoryName,input)==0)
		{
			while(curr<pGames->numCat)
			{
				strcpy(pGames->category[i].categoryName,pGames->category[i+1].categoryName);
			}
			pGames->numCat += - 1;
			printf("%s has been deleted:\n",input);
		}
		else
			printf("String not Found\n");
	}
	}	
	else
		printf("\nERROR: Category NOT Found");
		
	printf("\n");
	system("pause");
}

/*
	This function allows the user to input a category to be editted, and then asks
	the user which attributes he or she would like to change. (e.g. category name,
	questions, etc.)
*/
void
EditCategory(ptrGame pGames)
{
	printf("\nSELECTED: EDIT CATEGORY \n\n");
	printf("-----------------------------------------------------------");
	int i = 0, k, found = 0, ch, q, j =1;
	string10 input; 	char cDump;

	printf("\nEnter Category Name to be Edited: ");
	gets(input);
	
	if(pGames->numCat>0)
	{
		gets(input);
	for(i=0;i<pGames->numCat;i++)
		{
		if(strcasecmp(pGames->category[pGames->numCat].categoryName,input)==0)
		k = i;
		}	
	}	
	if(found == 1)
	{
		do
		{
			printf("\n1 - Category Name");
			printf("\n2 - questions");
			printf("\n3 - Back to Menu");
			printf("\n Enter choice: ");
			scanf("%d%c", &ch, &cDump);
			
			if(ch == 1)
			{
				printf("\nEnter [NEW] Category name: ");
				gets(input);
				strcpy(pGames->category[k].categoryName, input);
			}
			
			else if(ch == 2)
			{
				printf("\nQUESTIONS IN CATEGORY %s", input);
				for( i = 0 ; i < 5 ; i++)
				{
					printf("\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
					printf("\n%d. Question: %s ", j, pGames->category[k].questions[i].question);
					printf("\n	  > Answer: %s ", pGames->category[k].questions[i].answer); 
					printf("\n	  > Value : %d", pGames->category[k].questions[i].val); 
					j++;
				}
				printf("Enter Question Number you'd like to Edit: ");
				scanf("%d%c", &q, &cDump); 
				
				printf("\nEnter [NEW] Question: ");
				fgets(pGames->category[k].questions[q-1].question, 51, stdin);
				printf("\nEnter [NEW] Answer: ");
				fgets(pGames->category[k].questions[q-1].answer, 51, stdin);
				printf("\nEnter [NEW] Value:" );
				scanf("%d%c", &(pGames->category[k].questions[q-1].val),&cDump);
				
				printf("Question Number %d Edited.", q );
			}
		}while(ch != 3);
	}
	
	else
		printf("\nERROR: Category Not Found");
		
	printf("\n");
	system("pause");
}

/*
	This function allows the user to edit the final jeopardy question and answer
*/
void EditFJ(ptrGame pGames){ 
	printf("\nSELECTED: EDIT FINAL JEOPARDY \n\n");
	printf("-----------------------------------------------------------");
	printf("\nEnter Question: ");
	gets(pGames->FJeopardy.FJquestion);
	printf("\nEnter Answer: ");
	gets(pGames->FJeopardy.FJanswer);
	printf("\n");
	system("pause");
}

/*
	This function displays all thw questions and details by each Category
*/
void ViewByCateg(ptrGame pGames){
	printf("\nSELECTED: VIEW BY CATEGORY \n\n");
	printf("-----------------------------------------------------------");
	int i, k;	
	
	for(i=0; i < pGames->numCat ; i++) 
	{
		printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
		printf("\n		 CATEGORY - " ); 
		printf("%s", pGames->category[i].categoryName);
		printf("\n");
		for(k=0; k<6; k++ )
		{
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
			printf("\nQuestion %d : %s ", k+1, pGames->category[i].questions[k].question); 
			printf("\nAnswer : %s ", pGames->category[i].questions[k].answer); 
			printf("\nValue: %d", pGames->category[i].questions[k].val); 
			;
		}
		printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	}
	printf("\n");
	system("pause");
}

void ViewByVal(ptrGame pGames){
	printf("\nSELECTED: VIEW BY VALUE \n\n");
	printf("-----------------------------------------------------------");
	
	int y,i, k, j=1;
	if(pGames->numCat > 0)
		for(y=0; y <= 1000; y++) 
			for(i=0; i < pGames->numCat ; i++) 
				for(k=0; k<6; k++ )
					if(pGames->category[i].questions[k].val == y)
					{	
						printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
						printf("\nQuestion %d : %s ", j, pGames->category[i].questions[k].question); 
						printf("\nAnswer : %s ", pGames->category[i].questions[k].answer); 
						printf("\nValue: %d", pGames->category[i].questions[k].val); 
						printf("\n");
					}
		
	printf("\n");
	system("pause");
}

/*
	Function search : searches a keyword and then displays all the questions that have the substring
	entered by the user. 
*/
void Search(ptrGame pGames){	
	printf("SELECTED: SEARCH \n\n");
	printf("\n-----------------------------------------------------------\n");	
	int i, k, found = 0;
	string50 word;
	char cDump;
	
	printf("\nEnter keyword to be searched in the Jeopardy questions: ");
	scanf("%s%c", word, &cDump);
	
	for(i=0; i< pGames->numCat ; i++) 
		for(k = 0; k < 6; k++)
			if(strstr(pGames->category[i].questions[k].question, word ) != NULL ) 
			{
				printf("\n	> Category: %s", pGames->category[i].categoryName ); 
				printf("\n	> Question: %s", pGames->category[i].questions[k].question); 
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
				found = 1; 
			} 
	
	if(found == 0)
		printf("\nERROR: Keyword not found");
		
	printf("-----------------------------------------------------------");
	printf("\n");
	system("pause");
}

void
phaseOneMenu(ptrGame pGames)
{
	int choice;
	char cDump;
	do{
	system ("cls");	
   	printf("==================== Jeopardy Game Menu =====================");
	printf("\n 1 - Add Category");
    printf("\n 2 - Delete Category");
    printf("\n 3 - Edit Category");
    printf("\n 4 - Edit Final Jeopardy");
    printf("\n 5 - View by Category");
	printf("\n 6 - View by Value");
    printf("\n 7 - Search");
    printf("\n 8 - Exit");
	printf("\n===========================================================");

	printf("\nPlease input the [Number] of your desired Choice: ");
	scanf("%d%c", &choice,&cDump);
	
	switch(choice)
	{	
		case 1 : AddCategory(pGames);    break;
		case 2 : DeleteCategory(pGames); break;
		case 3 : EditCategory(pGames);   break;
		case 4 : EditFJ(pGames);            break;
		case 5 : ViewByCateg(pGames);    break;	
		case 6 : ViewByVal(pGames);      break;
		case 7 : Search (pGames);        break;
	}
	} while (choice!=8);
}

/*
	Add Game:     This function allows the user to add more games. Each game would have the
			      information in phase one and a string to store the game name.
*/
ptrGame
addGame(ptrGame pFirst)
{
	printf("\nSELECTED: ADD GAME \n\n");
	printf("-----------------------------------------------------------\n");
	string20 input;
	ptrGame pRun, pNew;
	
	printf("\n Name of Game: ");	
	gets(input);	
	
	pNew = malloc(sizeof(gameType));
	
		strcpy(pNew->gameName, input);	
		if (pFirst== NULL)
		{
			pNew->pNext = NULL;
			pFirst = pNew;
		}
		else
		{
			pRun=pFirst;
			while (pRun->pNext !=NULL)
			{
				pRun=pRun->pNext;
			}
			pNew->pNext = NULL;
			pRun->pNext = pNew;				
		}
	return pFirst;
}

/*
	This function gives an option whether or not to go automatically to the Phase
	One Functions after running addGame
*/
void
option(ptrGame pGames)
{
	char option;
	printf("\n\nWould you like to add information to the Game? (Y/N) \n");
	printf("Enter Option: ");
	scanf("%c", &option);

	if(toupper(option) == 'Y')
		phaseOneMenu(pGames);
	else if(toupper(option) == 'N'){
		printf("\n");
		system("pause"); 			}
	else printf("\n ERROR WRONG INPUT");
	
}
/*
	Delete Game:  This function deletes a node from the linked list of games. The user enters
				  the game name and if it’s found in the list then it is deleted.
*/

void
deleteGame(ptrGame pGames, ptrGame *pGame2)
{
	system ("cls");	
	printf("\nSELECTED: DELETE GAME \n\n");
	printf("-----------------------------------------------------------\n");
	printf("GAMES MADE: \n");
	viewGame(pGames);
	int  checker = 0; 
	string10 input;
	
	ptrGame pTemp = NULL; 
	printf("\n\nPlease enter name of game to Delete: ");
	gets(input);
	fflush(stdin);

	if(strcasecmp(input, pGames->gameName) == 0) 
	{
		*pGame2 = pGames->pNext; checker++;
	}
	else 
	{        
	while(pGames != NULL && checker == 0){
		if((strcasecmp(input, pGames->gameName)) == 0){ 
       		pTemp->pNext = pGames->pNext;
			checker++;
		}
		pTemp  = pGames;
        pGames = pGames->pNext;
	}
	}
	
	if(checker == 0 )
		printf("\nCategory %s was not found", input);
	else
		printf("\nSuccessfully Deleted %s", input);	
		
	printf("\n");
	system ("pause"); 
}

/*
	Select Game:  Chooses the game that is currently active/selected. Once a game in the list
   				  has been selected all the phase 1 function will apply to that particular node.
*/
ptrGame
selectGame(ptrGame pGames)
{
	system ("cls");	
	printf("\nSELECTED: SELECT GAME \n\n");
	printf("-----------------------------------------------------------\n");
	printf("GAMES MADE: \n");
	viewGame(pGames);
	string10 input;
	
	printf("\n\nPlease enter name of game to select: ");
	gets(input);
	fflush(stdin);
	while(pGames != NULL){
			if((strcasecmp(input, pGames->gameName)) == 0) 
				return pGames;
			pGames = pGames->pNext;       
		}
	
	printf("\nYou haven't added any Games yet");
	return NULL; 
	
	printf("\n");
	system ("pause"); 

}

/*
	View Games:   This shows a listing of all the game names you have added. 
*/
void
viewGame(gameType *pFirst)
{
	printf("\n	>>%s", pFirst->gameName);
	if(pFirst->pNext == NULL)
		return;
	
	viewGame(pFirst->pNext);
}

/*
	Save Game:    The function asks the user the game name and then saves the contents of the
				  appropriate node. This function allows the user to save a particular game to the text file
				  prescribed by the flash Jeopardy game. The game file should run in the flash game. Make
			      sure to check if it is complete and valid.
*/
void
saveGame(ptrGame pFirst)
{
	system ("cls");	
	printf("\nSELECTED: SELECT GAME \n\n");
	printf("-----------------------------------------------------------\n");
	FILE *fpCateg, *fpFJeop, *fpQuest, *fpAns;  
	string20 input;
	string50 fname ="column#-questions.txt",
			 fname2="column#-answers.txt";
	int i,j , found=0;
	
	printf("Please enter the game name you would like to save: ");
	gets(input); 
	while(pFirst!=NULL && found == 0)
	{
		if(strcasecmp(pFirst->gameName, input) == 0)
			found = 1;
		else
			pFirst = pFirst->pNext;
	}
	
	if(found ==1 ){
		fpCateg = fopen("categories.txt", "w");
		
		for( i=0; i<pFirst->numCat; i++)
		{	
			fprintf(fpCateg,"%s\n", pFirst->category[i].categoryName);
			fname[6]= (i+1) + '0';
			fname2[6]= (i+1) + '0';			
			fpQuest=fopen(fname,"w");
			fpAns=fopen(fname2,"w");
			printf("%s\n",fname);
			printf("%s\n",fname2);
			for(j = 0; j <=5 ; j++)
			{
				fprintf(fpQuest,"%s", pFirst->category[i].questions[j].question);
				fprintf(fpAns,  "%s", pFirst->category[i].questions[j].answer  );
			}
			fclose(fpQuest);
			fclose(fpAns);	
		}
		fpFJeop = fopen("finalj.txt","w");
		fprintf(fpFJeop,"%s\n%s", pFirst->FJeopardy.FJquestion
								, pFirst->FJeopardy.FJanswer  );
		fclose(fpCateg);
		fclose(fpFJeop);		 
		printf("Game was successfully saved!\n");
	}

	//fopen(<filename>,<filemode>) file name is a string, file mode r = read, w = write, a = append;
	
	else
		printf("ERROR: Game Input Not Found\n");
	
	printf("\n");
	system ("pause");  
}

/*
	Load Games:  adds the game to the lists of
			     games in the system. 
*/
gameType
loadGames()
{	 

	FILE *fpCateg, *fpFJeop, *fpQuest, *fpAns;
	gameType pNew; 
	int i, j, categ;
	string50 fname="column#-questions.txt",
			 fname2="column#-answers.txt";
	
	fpCateg= fopen("categories.txt", "r");
	for(categ = 0 ; categ < 6 ; categ++){
		fscanf(fpCateg,"%s",pNew.category[categ].categoryName);	
	}
	fclose(fpCateg);
	
	for(i=0;i<categ;i++){
		fname[6]= (i+1) + '0';
		fname2[6]= (i+1) + '0';			
		fpQuest=fopen(fname,"r");
		fpAns=fopen(fname2,"r");
			for(j=0;j<categ;j++){
				fgets(pNew.category[i].questions[j].question, 51, fpQuest ); 
				fgets(pNew.category[i].questions[j].answer, 51, fpAns); 
			}
	}
	
	fpFJeop = fopen("finalj.txt", "r");
	fgets(pNew.FJeopardy.FJquestion, 51, fpFJeop);
	fgets(pNew.FJeopardy.FJanswer, 51, fpFJeop );
	fclose(fpFJeop);
	fclose(fpQuest);
	fclose(fpAns); 
	printf("Success!\n\n");
	return pNew;
}


int 
main()
{
	char choice;
	ptrGame     pGames = NULL,	
				pNew = NULL,
				pRun;
				
	gameType newGame;
	string20 input;
	 
	do{
	system ("cls");	
   	printf("\n==================== Game Menu =====================");
	printf("\n [A] dd Game");
    printf("\n [D] elete Game"); 
    printf("\n [S] elect Game");
    printf("\n [V] iew Games");
    printf("\n [P] hase One (1) Functions");
    printf("\n [X] Save Game");
    printf("\n [L] oad Game");
	printf("\n [E] xit");
	printf("\n=================================================");

	if(pGames->gameName != NULL){
	printf("\n >>>Current Game Selected: %s", pGames->gameName);
	}
	
	printf("\n\n Enter Choice: ");
	scanf("%c", &choice);
	fflush(stdin);
	switch(toupper(choice))
	{	
		case 'A' : 	pGames = addGame(pGames);
				   	option(pGames);         
					break;
		case 'D' : 	if(pGames == NULL) printf("ADD A GAME!");
					else deleteGame(pGames, &pGames);     
					break;
		case 'S' :  if(pGames == NULL) printf("ADD A GAME!");
					else(selectGame(pGames));
				   	break;
		case 'V' : 	if   (pGames==NULL) printf("\nInput a Game!") ;
					else
					{
					system ("cls");	
					printf("SELECTED: VIEW GAMES \n\n");
					printf("-----------------------------------------------------------");
					viewGame(pGames); 
					
					printf("\n");
					system ("pause");
					}
					break;
		case 'P' : 	if(pGames == NULL) printf("ADD A GAME!");
					else phaseOneMenu(pGames);   
					break;	
		case 'X' : 	if(pGames == NULL) printf("ADD A GAME!");
					else saveGame(pGames);		break;
		case 'L' : 	printf("\nSELECTED: LOAD GAME \n\n");
					printf("-----------------------------------------------------------\n");					
					printf("\n Name of Game: ");							
					gets(input);
					fflush(stdin);
					newGame = loadGames();      
					strcpy(newGame.gameName, input);
					newGame.numCat = 5;
					pNew = &newGame;
					if (pGames== NULL)
					{
						pNew->pNext = NULL;
						pGames = pNew;
					}
					else
					{
						pRun=pGames;
						while (pRun->pNext !=NULL)
						{
							pRun=pRun->pNext;
						}
						pNew->pNext = NULL;
						pRun->pNext = pNew;				
					} 
					break;
		case 'E' : exit(1);
	}
	} while (choice!=8);
	
	return 0;
}



