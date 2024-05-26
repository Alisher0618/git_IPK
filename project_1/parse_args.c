/**
* @file parse_args.c
* @brief Parsing of CLI arguments
*
* @author Alisher Mazhirinov (xmazhi00)
*
*/
#include "parse_args.h"

/**
 * @brief Function for printing useful information
 */
void printHelp(){
    printf("==============================IPK24-CHAT PROTOCOL=============================\n\n");
    printf("-t -- Type of trasport protocol. Must be tcp or udp. \n");
    printf("-s -- Server IP or hostname.                         \n");
    printf("-p -- Server port.                                   \n");
    printf("-d -- UDP confirmation timeout. For TCP is nonmandatory.\n");
    printf("-r -- Maximum number of UDP retransmissions. For TCP is nonmandatory.\n");
    printf("-d and -r arguments are optional. By default timeout = 250, retranmission = 3.\n\n");
    printf("==============================IPK24-CHAT PROTOCOL=============================\n");
}

/**
 * @brief Function for parsing arguments from CLI
 * 
 * @param argc
 * @param argv 
 * @return struct of parse data
 */
struct InputData parseArguments(int argc, char** argv){
    int opt;
    struct InputData get_values;
    if(strcmp(argv[2], "udp") == 0){
        if(argc == 11){
            while((opt = getopt(argc, argv, "t:s:p:d:r:h:")) != -1){
                switch (opt)
                {
                case 't':       
                    get_values.protocol = optarg;     
                    if(!strcmp(get_values.protocol, "udp") && !strcmp(get_values.protocol, "tcp")){
                        printHelp();
                        exit(WRONG_PROTOCOL);
                    }
                    break;
                case 's':
                    get_values.host_name = optarg;
                    break;
                case 'p':
                    get_values.port = optarg;
                    if(atoi(get_values.port) > MAX_PORT && atoi(get_values.port) < MIN_PORT){
                        printHelp();
                        exit(WRONG_PORT);
                    }
                    break;
                case 'd':
                    if(atoi(optarg) < 250){
                        get_values.timeout = 250;
                        break;
                    }
                    get_values.timeout = atoi(optarg);
                    break;
                case 'r':
                    if(atoi(optarg) < 3){
                        get_values.retrans = 3;
                        break;
                    }
                    get_values.retrans = atoi(optarg);
                    break;
                case 'h':
                    printHelp();
                    exit(SUCCESS);
                case '?':
                    printHelp();
                    exit(INTERNAL_ERROR);
                }
            }
        }else if(argc == 7){
            while((opt = getopt(argc, argv, "t:s:p:h:")) != -1){
                switch (opt)
                {
                case 't':       
                    get_values.protocol = optarg;     
                    if(!strcmp(get_values.protocol, "udp") && !strcmp(get_values.protocol, "tcp")){
                        printHelp();
                        exit(WRONG_PROTOCOL);
                    }
                    break;
                case 's':
                    get_values.host_name = optarg;
                    break;
                case 'p':
                    get_values.port = optarg;
                    if(atoi(get_values.port) > MAX_PORT && atoi(get_values.port) < MIN_PORT){
                        printHelp();
                        exit(WRONG_PORT);
                    }
                    break;
                case 'h':
                    printHelp();
                    exit(SUCCESS);
                case '?':
                    printHelp();
                    exit(INTERNAL_ERROR);
                }
            }
            get_values.timeout = 250;
            get_values.retrans = 3;
        }
        
    }else if(strcmp(argv[2], "tcp") == 0){
        while((opt = getopt(argc, argv, "t:s:p:d:r:h:")) != -1){
            switch (opt)
            {
            case 't':       
                get_values.protocol = optarg;     
                if(!strcmp(get_values.protocol, "udp") && !strcmp(get_values.protocol, "tcp")){
                    printHelp();
                    exit(WRONG_PROTOCOL);
                }
                break;
            case 's':
                get_values.host_name = optarg;
                break;
            case 'p':
                get_values.port = optarg;
                if(atoi(get_values.port)  > MAX_PORT && atoi(get_values.port)  < MIN_PORT){
                    printHelp();
                    exit(WRONG_PORT);
                }
                break;
            case 'h':
                printHelp();
                exit(SUCCESS);
            case '?':
                printHelp();
                exit(INTERNAL_ERROR);
            }
        }
        get_values.timeout = 0;
        get_values.retrans = 0;
    }else{
        printHelp();
        exit(INTERNAL_ERROR);
    }
    
    return get_values;
}