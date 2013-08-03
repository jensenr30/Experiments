#define WORD_FILES_PATH "words\\"


void add_word_relationship(char * wordCurr, char * wordPrev){
	//generate a file name for this word
	char wordPrevFileName[MAX_WORD_LENGTH+10];
	strcpy(wordPrevFileName, WORD_FILES_PATH);
	strcat(wordPrevFileName, wordPrev);
	strcat(wordPrevFileName, ".txt");
	
	FILE *wordPrevFile = fopen(wordPrevFileName, "a");
	if(wordPrevFile == NULL) {
		printf("failed to open %s\n",wordPrevFileName);
		return; // quit if you cannot open it.
	}
	
	//assuming the file is open, add the current word to the list
	fprintf(wordPrevFile, "%s\n", wordCurr);
	fclose(wordPrevFile);
}






FILE *choose_file(){
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "txt";
	ofn.lpstrInitialDir = ".";
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR | OFN_FILEMUSTEXIST;

	if(GetOpenFileName(&ofn))
	{
		printf("Analyzing %s", szFileName);
	    return fopen(szFileName, "r");
	}
	else return NULL;
}
