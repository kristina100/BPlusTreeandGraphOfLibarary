#include"FileDo.h"
#include"BPlusTree.h"
#include"Global.h"

/**
* Read_Buffer(char *input_file) -> buffer
*/
void Read_Buffer(char *input_file) {
    printf("%s",input_file);
    FILE* fin = fopen(input_file, "a+");
//    FILE* fin = fopen(input_file, "r+");
//    FILE* fin = fopen(input_file, "w+");
    if (fin == NULL) {
        fputs("File Error\n", stderr);
        exit(1);
    }
    // obtain file size
    fseek(fin, 0, SEEK_END);
    fsize = ftell(fin);
    rewind(fin);
    // allocate memory
    buffer = (char*)malloc(sizeof(char) * fsize);
    if (buffer == NULL) {
        fputs("Memory Error\n", stderr);
        exit(2);
    }
    // read to buffer[]
    fread(buffer, 1, fsize, fin);
    fclose(fin);
}

/** Read and insert records into B+tree */
void Read_Data_And_Insert() {
    int rid = 0;
    int cur = 0;
    while (1) {
        while (cur < fsize && !('0' <= buffer[cur] && buffer[cur] <= '9')) cur++; // end of file
        if (cur == fsize) break;

        rid++;
        if (rid % 100000 == 0) printf("now inserting the %d th record ..\n", rid);
        new_key = 0;
        new_pos = cur;
        while (buffer[cur] != ' ' && buffer[cur] != '\t') {
            new_key = new_key * 10 + (buffer[cur] - '0');
            cur++;
        }
        cur++;
        new_len = 0;
        while (buffer[cur] == ' ') cur++; // util meet a character
        while (cur < fsize && buffer[cur] != '\n') {
            new_st[new_len++] = buffer[cur++];
        }
        new_st[new_len] = '\0';
        char* value = (char*)malloc(sizeof(char) * new_len);
        strcpy(value, new_st);
        keys[key_num++] = new_key;
        //if (BPlusTree_Insert(new_key, new_pos, value) == true) validRecords++; // for "ex-data.txt", valid = 9950138
    }
    free(buffer);
    buffer = NULL;
}


/** Modify (key, value) on data file */
int File_Modify(int pos, int key, char *value) {
    int old_key, old_len, len = strlen(value), i;
    char old_value[12];

    FILE* file = fopen(input_file, "r+");
    fseek(file, pos, SEEK_SET);
    fscanf(file, "%d %s", &old_key, old_value); // read old
    old_len = strlen(old_value);

    if (len > old_len) return false; // conflict
    // rewrite
    fseek(file, pos - ftell(file), SEEK_CUR); // return to previous position
    fprintf(file, "%d\t%s", key, value);
    for (i = len; i < old_len; i++) fprintf(file, " "); // space fill blanks
    fclose(file);
    return true;
}


/** Delete (key, value) on data file */
void File_Delete(int pos) {
    int old_key, i;
    char old_value[12];

    FILE* file = fopen(input_file, "r+");
    fseek(file, pos, SEEK_SET);
    fscanf(file, "%d %s", &old_key, old_value); // read old
    int end_pos = ftell(file);

    printf("%d %d\n", pos, end_pos);
    // rewrite
    fseek(file, pos - end_pos, SEEK_CUR); // return to previous position
    for (i = pos; i < end_pos; i++) fprintf(file, " "); // space fill blanks
    fclose(file);
}


/** Insert (key, value) on data file */
int File_Insert(int new_key, char* new_st) {
    FILE* file = fopen(input_file, "r+");
    fseek(file, 0, SEEK_END);
    int new_pos = ftell(file);

    fprintf(file, "%d %s\n", new_key, new_st);
    fclose(file);
    return new_pos;
};


void build_test() {
    double start_time, end_time, tot_time = 0;
    int built = false;

    // MaxChildNumber
    printf("input depth: ");
    int depth;
    scanf("%d", &depth);
    int maxCh = 2;
    while (1) {
        int leaves = 1, i;
        for (i = 0; i < depth; i++)
        {
            leaves *= maxCh;
            if (leaves > TotalRecords)
                break;
        }
        if (leaves > TotalRecords) break;
        maxCh++;
    }
    printf("Desired depth = %d, calculated maxChildNumber = %d\n", depth, maxCh);
    BPlusTree_SetMaxChildNumber(maxCh);

    // build
    int build_num = 10, i;
    for (i = 0; i < build_num; i++) {
        printf("=============== %d ==========\n", i);
        // read buffer
        Read_Buffer(input_file);
        start_time = clock();
        // B+tree initialize
        BPlusTree_Init();
        // args
        built = false;
        validRecords = 0;
        key_num = 0;
        // build
        built = true;
        Read_Data_And_Insert();
        end_time = clock();
        tot_time += (end_time - start_time);
        printf("Valid Records inserted on B+tree = %d\n", validRecords);
        printf("Total number of B+tree nodes = %d\n", BPlusTree_GetTotalNodes());
        printf("this time costs %lf s\n\n", (end_time - start_time) / CLOCKS_PER_SEC);
        BPlusTree_Destroy();
    }
    printf("build %d times, average cost is %lf s\n", build_num, tot_time / CLOCKS_PER_SEC / build_num);
}

void query_key_test() {
    double start_time, end_time;
    int built = false;

    Read_Buffer(input_file);
    // B+tree initialize
    BPlusTree_Init();
    // MaxChildNumber
    printf("input depth: ");
    int depth;
    scanf("%d", &depth);
    int maxCh = 2;
    while (1) {
        int leaves = 1, i;
        for (i = 0; i < depth; i++) {
            leaves *= maxCh;
            if (leaves > TotalRecords) break;
        }
        if (leaves > TotalRecords) break;
        maxCh++;
    }
    printf("Desired depth = %d, calculated maxChildNumber = %d\n", depth, maxCh);
    BPlusTree_SetMaxChildNumber(maxCh);
    // build
    built = true;
    start_time = clock();
    Read_Data_And_Insert();
    end_time = clock();
    printf("Valid Records inserted on B+tree = %d\n", validRecords);
    printf("Total number of B+tree nodes = %d\n", BPlusTree_GetTotalNodes());
    printf("Build B+tree costs %lf s\n", (end_time - start_time) / CLOCKS_PER_SEC);
    // query
    start_time = clock();
    int key, i;
    srand((unsigned)time(NULL));
    int query_num = 10;
    for (i = 0; i < query_num; i++) {
        key = keys[rand() % key_num];
        BPlusTree_Query_Key(key);
    }
    end_time = clock();
    printf("query %d ranges, average cost is %lf s\n", query_num, (end_time - start_time) / CLOCKS_PER_SEC / query_num);
    BPlusTree_Destroy();
}

void query_range_test() {
    double start_time, end_time;
    int built = false;

    Read_Buffer(input_file);
    // B+tree initialize
    BPlusTree_Init();
    // MaxChildNumber
    printf("input depth: ");
    int depth;
    scanf("%d", &depth);
    int maxCh = 2;
    while (1) {
        int leaves = 1, i;
        for (i = 0; i < depth; i++) {
            leaves *= maxCh;
            if (leaves > TotalRecords) break;
        }
        if (leaves > TotalRecords) break;
        maxCh++;
    }
    printf("Desired depth = %d, calculated maxChildNumber = %d\n", depth, maxCh);
    BPlusTree_SetMaxChildNumber(maxCh);
    // build
    built = true;
    start_time = clock();
    Read_Data_And_Insert();
    end_time = clock();
    printf("Valid Records inserted on B+tree = %d\n", validRecords);
    printf("Total number of B+tree nodes = %d\n", BPlusTree_GetTotalNodes());
    printf("Build B+tree costs %lf s\n", (end_time - start_time) / CLOCKS_PER_SEC);
    // query
    start_time = clock();
    int key, i;
    srand((unsigned)time(NULL));
    int query_num = 10;
    for (i = 0; i < query_num; i++) {
        int r = ((long long)(rand() % MAX_KEY) * (rand() % MAX_KEY)) % MAX_KEY + 1;
        int l = ((long long)(rand() % MAX_KEY) * (rand() % MAX_KEY)) % r + 1;
        printf("range = (%d, %d)\n", l, r);
        BPlusTree_Query_Range(l, r);
    }
    end_time = clock();
    printf("query %d ranges, average cost is %lf s\n", query_num, (end_time - start_time) / CLOCKS_PER_SEC / query_num);
    BPlusTree_Destroy();
}

void modify_test() {
    double start_time, end_time;
    int built = false;

    Read_Buffer(input_file);
    // B+tree initialize
    BPlusTree_Init();
    // MaxChildNumber
    printf("input depth: ");
    int depth;
    scanf("%d", &depth);
    int maxCh = 2;
    while (1) {
        int leaves = 1, i;
        for (i = 0; i < depth; i++) {
            leaves *= maxCh;
            if (leaves > TotalRecords) break;
        }
        if (leaves > TotalRecords) break;
        maxCh++;
    }
    printf("Desired depth = %d, calculated maxChildNumber = %d\n", depth, maxCh);
    BPlusTree_SetMaxChildNumber(maxCh);
    // build
    built = true;
    start_time = clock();
    Read_Data_And_Insert();
    end_time = clock();
    printf("Valid Records inserted on B+tree = %d\n", validRecords);
    printf("Total number of B+tree nodes = %d\n", BPlusTree_GetTotalNodes());
    printf("Build B+tree costs %lf s\n", (end_time - start_time) / CLOCKS_PER_SEC);
    // modify
    start_time = clock();
    int key, i, j;
    srand((unsigned)time(NULL));
    int mod_num = 10;
    for (i = 0; i < mod_num; i++) {
        new_key = keys[rand() % key_num];
        new_len = 10;
        for (j = 0; j < new_len; j++) new_st[j] = 'a' + rand() % 26;

        char* value = (char*)malloc(sizeof(char) * strlen(new_st));
        strcpy(value, new_st);
        int pos = BPlusTree_Find(new_key);
        if (pos != -1) { // found
            if (File_Modify(pos, new_key, new_st)) { // file modify success
                // BPlusTree_Modify(new_key, value);
                //printf("Modify success.\n");
            } else {
                //printf("Modify failed, the new value is too long to store in file\n");
            }
        } else {
            printf("Modify failed, do not have the given key on B+tree.\n");
        }
    }
    end_time = clock();
    printf("modify %d elements, average cost is %lf s\n", mod_num, (end_time - start_time) / CLOCKS_PER_SEC / mod_num);
    BPlusTree_Destroy();
}

void delete_test() {
    double start_time, end_time;
    int built = false;

    Read_Buffer(input_file);
    // B+tree initialize
    BPlusTree_Init();
    // MaxChildNumber
    printf("input depth: ");
    int depth;
    scanf("%d", &depth);
    int maxCh = 2;
    while (1) {
        int leaves = 1, i;
        for (i = 0; i < depth; i++) {
            leaves *= maxCh;
            if (leaves > TotalRecords) break;
        }
        if (leaves > TotalRecords) break;
        maxCh++;
    }
    printf("Desired depth = %d, calculated maxChildNumber = %d\n", depth, maxCh);
    BPlusTree_SetMaxChildNumber(maxCh);
    // build
    built = true;
    start_time = clock();
    Read_Data_And_Insert();
    end_time = clock();
    printf("Valid Records inserted on B+tree = %d\n", validRecords);
    printf("Total number of B+tree nodes = %d\n", BPlusTree_GetTotalNodes());
    printf("Build B+tree costs %lf s\n", (end_time - start_time) / CLOCKS_PER_SEC);
    // delete
    start_time = clock();
    int key, i;
    srand((unsigned)time(NULL));
    int del_num = 10;
    for (i = 0; i < del_num; i++) {
        key = keys[rand() % key_num];
        int pos = BPlusTree_Find(key);
        if (pos != -1) { // found
            File_Delete(pos);
            BPlusTree_Delete(key);
            //printf("Delete success.\n");
        } else {
            //printf("Delete failed, do not have the given key on B+tree.\n");
        }
    }
    end_time = clock();
    printf("delete %d elements, average cost is %lf s\n", del_num, (end_time - start_time) / CLOCKS_PER_SEC / del_num);
    BPlusTree_Destroy();
}