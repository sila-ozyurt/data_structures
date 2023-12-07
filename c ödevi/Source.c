//program to create 2 circular queue in 20-sized int array according to commands which is taken from the input.txt file.
// If there is empty spaces, queues can have more than 10 elements.
//print operation will be on console
//front of queue1 has to start from index 0 and front of queue2 has to start from index 10. It may change as we enqueue or dequeue

#include<stdio.h>
#include <stdlib.h>

//we define array size
#define MAX_SIZE 20

int array[MAX_SIZE];

typedef struct CircularQueue {
	int front;
	int rear;
	int size;
}cQUEUE;

cQUEUE q1, q2;


//functions which are starting with 'take..' keyword will be used for taking commands from txt file
void takeCommands(FILE* inputFile);
void takeEnqueue(char* queueName, int value);
void takeDequeue(char* queueName);
void takePrint(cQUEUE* q);

//assign beginning front values of queues 
void initializeQueue(cQUEUE* q);

int isEmptyQueue(cQUEUE* q);
int isFullQueue(cQUEUE* q);

void enqueue(cQUEUE* q, int data);
void dequeue(cQUEUE* q);
void print(cQUEUE *q);



int main() {
	initializeQueue(&q1, 0);
	initializeQueue(&q2, 10);

	FILE* inputFile = fopen("input.txt", "r");

	if (inputFile == NULL) {
		printf("ERROR >>>> input.txt file cannot be opened!!!!!!");
		return 1;
	}

	takeCommands(inputFile);

	fclose(inputFile);

	return 0;
}



void initializeQueue(cQUEUE* q, int front) {
	q->front = front;
	q->rear = front;
	q->size = 0;
}

//function to take the commands from txt file
void takeCommands(FILE* inputFile) {

	char command[20];
	char queue[10];
	int value;

	// it will loop till the end of the file
	while (fscanf(inputFile, "%s", command) != EOF) {

		if (strcmp(command, "ENQUEUE") == 0) {
			fscanf(inputFile, "%s %d", queue, &value);
			takeEnqueue(queue, value);
		}
		else if (strcmp(command, "DEQUEUE") == 0) {
			fscanf(inputFile, "%s", queue);
			takeDequeue(queue);
		}
		else if (strcmp(command, "PRINT") == 0) {
			fscanf(inputFile, "%s", queue);
			if (strcmp(queue, "FIRST") == 0) {
				print(&q1);
			}
			else if (strcmp(queue, "SECOND") == 0) {
				print(&q2);
			}
		}
	}
}

//function to call actual enqueue func according to the queues(1 or 2)
void takeEnqueue(char* queueName, int value) {
	if (strcmp(queueName, "FIRST") == 0) {
		enqueue(&q1, value);
	}
	else if (strcmp(queueName, "SECOND") == 0) {
		enqueue(&q2, value);
	}
}

//function to call actual dequeue func according to the queues(1 or 2)
void takeDequeue(char* queueName) {
	if (strcmp(queueName, "FIRST") == 0) {
		dequeue(&q1);
	}
	else if (strcmp(queueName, "SECOND") == 0) {
		dequeue(&q2);
	}
}

//function to control if queue is empty
int isEmptyQueue(cQUEUE* q) {
	if (q == &q1 && q1.front == q1.rear && (q1.size == 0)) {
		printf("Queue FIRST is empty\n");
		return 1;
	}
	else if (q == &q2 && q2.front == q2.rear && (q2.size == 0)) {
		printf("Queue SECOND is empty\n");
		return 1;
	}

	return 0;
}

//function to control if queue is full
int isFullQueue(cQUEUE* q) {
	if (q == &q1 && (q1.rear + 1) % MAX_SIZE == q2.front) {
		printf("Queue FIRST is full\n");
		return 1;
	}
	else if (q == &q2 && (q2.rear + 1) % MAX_SIZE == q1.front) {
		printf("Queue SECOND is full\n");
		return 1;
	}
	return 0;
}

//function to operate enqueue 
void enqueue(cQUEUE* q, int data) {
	if (isFullQueue(q)) {
		return;
	}
	else {
		array[q->rear] = data;
		q->rear = (q->rear + 1) % MAX_SIZE;
		q->size++;
		(q == &q1) ? printf("%d is inserted to the queue FIRST\n", data) : printf("%d is inserted to the queue SECOND\n", data);
	}
}

//function to operate dequeue
void dequeue(cQUEUE* q) {

	if (isEmptyQueue(q)) {
		return;
	}
	else {
		if (q->front == q->rear) {

			(q == &q1) ? printf("%d is deleted the queue FIRST\n", array[q->front]) : printf("%d is deleted from the queue SECOND\n", array[q->front]);
			q->size=0;

			//not to write on the index which we newly delete from.
			// suppose queue 2 is full from 10th index to 19th and we dequeue all elements
			//according to this algorithm front2=rear2=19 and we need to update front to 0.
			//rear will be updated by enqueue.Enqueue function first increases and pleaces.
			q->front += 1;
			q->front = (q->front) % MAX_SIZE;
	

			return;
		}
		(q == &q1) ? printf("%d is deleted the queue FIRST\n", array[q->front]) : printf("%d is deleted from the queue SECOND\n", array[q->front]);
		q->front = (q->front + 1) % MAX_SIZE;
		q->size--;
	}
}

//function to operate print 
void print(cQUEUE *q) {
	//not to change real fron,rear and size values, we need to have temp front,rear and size
	int tFront;
	int tRear;
	int tSize;

	//if queue gets empty again, apart from the beginning state
	if (q == &q1) {
		tFront = q1.front;
	    tRear = q1.rear-1;
		tSize = q1.size;
		printf("QUEUE: FIRST  FRONT:%d  REAR:%d  SIZE:%d\n",q1.front,q1.rear,q1.size);
	}
	else if (q == &q2) {
		tFront = q2.front;
		tRear = q2.rear-1;
		tSize = q2.size;
		printf("QUEUE: SECOND  FRONT:%d  REAR:%d  SIZE:%d\n", q2.front, q2.rear, q2.size);
	}
	
	
	while (tFront <= tRear && tSize > 0) {
		printf("%d\t", array[tFront]);
		tFront++;
	}

	if (tSize == 0) {
		printf("NO_CONTENT\n");
	}
	else {
		printf("\n");
	}
}



