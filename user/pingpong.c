#include "kernel/types.h"
#include "user/user.h"


int main() {

    int file_descriptor1[2];
    int file_descriptor2[2];

    char buffer[5];

    pipe(file_descriptor1);
    pipe(file_descriptor2);

    int pid = fork();

    if (pid > 0) {

        char request[] = "ping";

        close(file_descriptor1[0]);								 // close reading
        write(file_descriptor1[1], request, sizeof request);	 // write the request
        close(file_descriptor1[1]);                              // close writing

        close(file_descriptor2[1]);                              // close writing
        read(file_descriptor2[0], buffer, sizeof buffer); 		 // read the response
        printf("%d: got %s\n", getpid(), buffer);
        close(file_descriptor2[0]);                              // close reading


    } else if (pid == 0) {

        char response[] = "pong";

        close(file_descriptor1[1]);                              // close writing
        read(file_descriptor1[0], buffer, sizeof buffer);        // read the request
        printf("%d: got %s\n", getpid(), buffer);
        close(file_descriptor1[0]);                              // close reading

        close(file_descriptor2[0]);                              // close reading
        write(file_descriptor2[1], response, sizeof response);   // write the response
        close(file_descriptor2[1]); 							 // close writing

    } else {
        printf("Fork error\n");
    }

    exit(0);
}
