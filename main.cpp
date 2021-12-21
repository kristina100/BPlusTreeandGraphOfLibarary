#include"Common.h"
#include"BPlusTree.h"
#include"FileDo.h"
#include"Global.h"

/** Show Help */
void ShowHelp() {
    printf("\nType your operation:\n");
    printf("  0) Test Initialize\n");
    printf("  1) Set Depth\n");
    printf("  2) Set MaxChildNumber\n");
    printf("  3) Build Tree\n");
    printf("  4) Query on a key\n");
    printf("  5) Query on keys of range [l, r]\n");
    printf("  6) Modify value on a key\n");
    printf("  7) Delete value on a key\n");
    printf("  8) Insert new record\n");
    printf("  9) Quit\n");
}

void MainLoop() {
    double start_time, end_time;
    int built = false;

    // Read data to buffer
    Read_Buffer(input_file);
    // B+tree initialize
    BPlusTree_Init();
    while (1) {
        ShowHelp();
        int request;
        scanf("%d", &request);
        switch (request)
        {
            case 0:
            {
                // Read data to buffer
                if (buffer != NULL) free(buffer);
                Read_Buffer(input_file);
                // B+tree initialize
                BPlusTree_Init();
                // args
                built = false;
                validRecords = 0;
                
            }break;

            case 1:
            {
                // Set Depth
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
                
            }break;

            case 2:
            {
                // Set MaxChildNumber
                printf("input MaxChildNumber: ");
                int maxCh;
                scanf("%d", &maxCh);
                BPlusTree_SetMaxChildNumber(maxCh);
                
            }break;
            
            case 3:
            {
                // Build B+tree
                if (built == true)
                {
                    printf("You have built the B+tree\n");
                    break;
                }
                built = true;
                start_time = clock();
                Read_Data_And_Insert();
                end_time = clock();
                printf("Valid Records inserted on B+tree = %d\n", validRecords);
                printf("Total number of B+tree nodes = %d\n", BPlusTree_GetTotalNodes());
                printf("Build B+tree costs %lf s\n", (end_time - start_time) / CLOCKS_PER_SEC);
                
            }break;
            
            case 4:
            {
                // Query on a key
                printf("input the key: ");
                int key;
                scanf("%d", &key);
                start_time = clock();
                BPlusTree_Query_Key(key);
                end_time = clock();
                printf("Query on a key, costs %lf s\n", (end_time - start_time) / CLOCKS_PER_SEC);
                
            }break;

            case 5:
            {
                // Query on a range [l, r]
                printf("input range [l, r]: ");
                int l, r;
                scanf("%d %d", &l, &r);
                if (l > r)
                {
                    printf("input illegal\n");
                    break;
                }
                start_time = clock();
                BPlusTree_Query_Range(l, r);
                end_time = clock();
                printf("Query on a range, costs %lf s\n", (end_time - start_time) / CLOCKS_PER_SEC);
                
            }break;

            case 6:
            {
                // Modify value on a key
                printf("input (key, value): ");
                scanf("%d,%s", &new_key, new_st);
                char* value = (char*)malloc(sizeof(char) * strlen(new_st));
                strcpy(value, new_st);
                start_time = clock();
                int pos = BPlusTree_Find(new_key);
                if (pos != -1)
                {
                    // found
                    if (File_Modify(pos, new_key, new_st)) {
                        // file modify success
                        BPlusTree_Modify(new_key, value);
                        printf("Modify success.\n");
                    } else {
                        printf("Modify failed, the new value is too long to store in file\n");
                    }
                } else {
                    printf("Modify failed, do not have the given key on B+tree.\n");
                }
                end_time = clock();
                printf("Modify value on a key, costs %lf s\n", (end_time - start_time) / CLOCKS_PER_SEC);
                
            }break;

            case 7: {
                // Delete value on a key
                printf("input key: ");
                int key;
                scanf("%d", &key);
                start_time = clock();
                int pos = BPlusTree_Find(key);
                if (pos != -1) { // found
                    File_Delete(pos);
                    BPlusTree_Delete(key);
                    printf("Delete success.\n");
                } else {
                    printf("Delete failed, do not have the given key on B+tree.\n");
                }
                end_time = clock();
                printf("Delete value on a key, costs %lf s\n", (end_time - start_time) / CLOCKS_PER_SEC);
               
            }break;

            case 8: {
                printf("input (key, value): ");
                /*
                    根据提示，两个输入之间添加逗号，但不完善
                */
                scanf("%d, %s", &new_key, new_st);
                char* value = (char*)malloc(sizeof(char) * new_len);
                strcpy(value, new_st);

                int pos = BPlusTree_Find(new_key);
                if (pos == -1) {
                    new_pos = File_Insert(new_key, new_st);
                    keys[key_num++] = new_key;
                    BPlusTree_Insert(new_key, new_pos, value);
                    validRecords++;
                    printf("Insert success.\n");
                } else {
                    printf("Insert failed, the key already exist.\n");
                }
                
            }break;

            case 9: return;
            default: break;
        }
    }
    BPlusTree_Destroy();
}

int main(int argc, char *argv[]) {
    // set input_file, output_file
    strcpy(input_file, "small-data.txt");
    strcpy(output_file, "out.txt");
    if (argc == 2) strcpy(input_file, argv[1]);

    // MainLoop (for presentation)
    MainLoop();

//	build_test();
//	query_key_test();
//	query_range_test();
//	modify_test();
//	delete_test();
    return 0;
}
