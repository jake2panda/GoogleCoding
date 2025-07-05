#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    int gym;
    int school;
    int store;
}Tuple;



typedef struct Node {
    int gym;
    int school;
    int store;
    struct Node *next;
    struct Node *prev;
}Node;


Node *createNode(int gym, int school, int store) {
    Node *new_node = (Node *)malloc(100);
    if (new_node == NULL) {
        printf("memory error\n");
        exit(EXIT_FAILURE);
    }

    new_node->gym = gym;
    new_node->school = school;
    new_node->store = store;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}


void insertAtStart(Node **head, int gym, int school, int store) {
    Node *new_node = createNode(gym, school, store);
    new_node->next = *head;
    new_node->prev = NULL;
    if (*head != NULL) {
        (*head)->prev = new_node;
    }
    *head = new_node;
}



void print_result(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d -- ", arr[i]);
    }

    printf("\n");
}



int local_min(int arr[],int len) {
    int min = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] < min) {
            min = arr[i];
        } 
    }

    return min;
}


int decide_appartment(Tuple appart[], int len) {
    int distanceStore[len];

    for (int i = 0; i < len; i++) {
        Tuple tmp = appart[i];
        distanceStore[i] = tmp.gym + tmp.school + tmp.store;
    }

    //print_result(distanceStore, len);

    int mininum_distance = local_min(distanceStore, len);

    int finalPosition = 0;
    for (int i = 0; i < len; i++) {
        if (distanceStore[i] == 2) {
            Tuple check = appart[i];
            if (check.gym == mininum_distance || check.school == mininum_distance || check.store == mininum_distance) {
                continue;
            }
            finalPosition = i;
            break;
        }
    }

    return finalPosition;
}


int solve(Node **head, int numberOfBlock) {
    Tuple appartmentResult[numberOfBlock];

    int gymDist = 0;
    int schoolDist = 0;
    int storeDist = 0;
    int index = 0;
    Node *cur = *head;

    while (index < numberOfBlock && cur != NULL) {
        if (!cur->gym) {

            Node *gym_search_forward = cur->next;
            int forwardDistanceCount = 1;
            int leftGymDistance = 0;
            int leftGymSensor = 0;
            while(gym_search_forward != NULL) {
                if (gym_search_forward == NULL) {
                    break;
                }
                if (gym_search_forward->gym) {
                    leftGymDistance += forwardDistanceCount;
                    leftGymSensor = 1;
                    break;
                }
                forwardDistanceCount++;
                gym_search_forward = gym_search_forward->next;
            }

            // now search backward..
            Node *gym_search_backward = cur->prev;
            int backwardDistanceCount = 1;
            int rightGymDistance = 0;
            int rightGymSensor = 0;
            while (gym_search_backward != NULL) {
                if (gym_search_backward == NULL) {
                    break;
                }
                if (gym_search_backward->gym) {
                    rightGymDistance += backwardDistanceCount;
                    rightGymSensor = 1;
                    break;
                }
                backwardDistanceCount++;
                gym_search_backward = gym_search_backward->prev;
            }

            // here chosing which distance is less than other.
            if (leftGymSensor && rightGymSensor) {
                if (leftGymDistance < rightGymDistance) {
                    gymDist += leftGymDistance;
                } else {
                    gymDist += rightGymDistance;
                }
            } else if (leftGymSensor) {
                gymDist += leftGymDistance;
            } else if (rightGymSensor) {
                gymDist += rightGymDistance;
            }
        } else {
            gymDist += 0;
        }

        if (!cur->school) {
            Node *school_search_forward = cur->next;
            int forwardDistanceCount = 1;
            int leftSchoolDistance = 0;
            int leftSensor = 0;
            while(school_search_forward != NULL) {
                if (school_search_forward == NULL) {
                    break;
                }
                if (school_search_forward->school) {
                    leftSchoolDistance += forwardDistanceCount;
                    leftSensor = 1;
                    break;
                }
                forwardDistanceCount++;
                school_search_forward = school_search_forward->next;
            }

            // now search backward..
            Node *school_search_backward = cur->prev;
            int backwardDistanceCount = 1;
            int rightSchoolDistance = 0;
            int rightSensor = 0;
            while (school_search_backward != NULL) {
                if (school_search_backward == NULL) {
                    break;
                }
                if (school_search_backward->school) {
                    rightSchoolDistance += backwardDistanceCount;
                    rightSensor = 1;
                    break;
                }
                backwardDistanceCount++;
                school_search_backward = school_search_backward->prev;
            }

            if (leftSensor && rightSensor) {
                if (leftSchoolDistance < rightSchoolDistance) {
                    schoolDist += leftSchoolDistance;
                } else {
                    schoolDist += rightSchoolDistance;
                }
            } else if (leftSensor) {
                schoolDist += leftSchoolDistance;
            } else if (rightSensor) {
                schoolDist += rightSchoolDistance;
            }
        } else {
            schoolDist += 0;
        }

        if (!cur->store) {
            Node *store_search_forward = cur->next;
            int forwardDistanceCount = 1;
            int leftStoreDistance = 0;
            int leftSensor = 0;
            while(store_search_forward != NULL) {
                if (store_search_forward == NULL) {
                    break;
                }
                if (store_search_forward->store) {
                    leftStoreDistance += forwardDistanceCount;
                    leftSensor = 1;
                    break;
                }
                forwardDistanceCount++;
                store_search_forward = store_search_forward->next;
            }

            // now search backward..
            Node *store_search_backward = cur->prev;
            int backwardDistanceCount = 1;
            int rightStoreDistance = 0;
            int rightSensor = 0;
            while (store_search_backward != NULL) {
                if (store_search_backward == NULL) {
                    break;
                }
                if (store_search_backward->store) {
                    storeDist += backwardDistanceCount;
                    rightSensor = 1;
                    break;
                }
                backwardDistanceCount++;
                store_search_backward = store_search_backward->prev;
            }

            if (leftSensor && rightSensor) {
                if (leftStoreDistance < rightStoreDistance) {
                    storeDist += leftStoreDistance;
                } else {
                    storeDist += rightStoreDistance;
                }
            } else if (leftSensor) {
                storeDist += leftStoreDistance;
            } else if (rightSensor) {
                storeDist += rightStoreDistance;
            }
        } else {
            storeDist += 0;
        }


       // printf("index : %d gymDist - %d <-> schoolDist - %d <-> storeDist - %d \n", index, gymDist, schoolDist, storeDist);

        Tuple blk1 = {
            .gym = gymDist,
            .school = schoolDist,
            .store = storeDist,
        };

        appartmentResult[index] = blk1;

        index++;
        cur = cur->next;
        gymDist = 0;
        schoolDist = 0;
        storeDist = 0;

    }


    int appartmentIndex = decide_appartment(appartmentResult, numberOfBlock);

    Tuple show_re = appartmentResult[appartmentIndex];

    printf("[----        Appartment-Index : %d      -----]\n", appartmentIndex);
    printf("==============================================\n");
    printf("----------------------------------------------\n");
    printf("       gym   |     school     |   store         \n");
    printf("----------------------------------------------\n");

    printf("       %d     -       %d        -    %d\n", show_re.gym, show_re.school, show_re.store);


    printf("\n");

}


int main() {


    Node *head = NULL;

    insertAtStart(&head, 0, 1, 0);
    insertAtStart(&head, 1, 0, 0);
    insertAtStart(&head, 1, 1, 0);
    insertAtStart(&head, 0, 1, 0);
    insertAtStart(&head, 0, 1, 1);

    solve(&head, 5);

}


