//
//  main.c
//  klausur_c_observer
//
//  Created by ursus on 10.03.16.
//  Copyright © 2016 Ursus Schneider. All rights reserved.
//

#include <stdio.h>

#define C_MAX_OBSERVER 10

typedef struct _observer observer_t;
typedef struct _subject subject_t;

typedef struct _subject {
    
    void (* attach) (subject_t * self, observer_t * function);
    void (* detach) (subject_t * self, observer_t * function);
    void (* notify) (subject_t * self, char * news);
    
    observer_t * observerCollection [C_MAX_OBSERVER];
    int observerCount;
    
} subject_t;

typedef struct _observer {
    
    void (* notify) (char * news);
    
} observer_t;

void attach (subject_t * self, observer_t * function) {
    
    // check for end of list
    if (self->observerCount == (C_MAX_OBSERVER - 1))
        return;
    
    // find an empty slot
    int i = 0;
    while (self->observerCollection [i] != 0)
        i++;
    
    self->observerCollection [i] = function;
    self->observerCount++;
}

void detach (subject_t * self, observer_t * function) {

    // remove the observer you do not need
    for (int i = 0; i < C_MAX_OBSERVER; i++)
        if (self->observerCollection [i] == function)
            self->observerCollection [i] = 0;
    
    // one observer less
    self->observerCount--;
}

void notify (subject_t * self, char * news) {
    printf ("Sending the message to the observers\n");
    for (int i = 0; i < C_MAX_OBSERVER; i++)
        if (self->observerCollection [i] != 0)
            self->observerCollection [i]->notify (news);
    printf ("====================================\n");
    
}

// the actual observer functions
void orf1 (char * news) {
    printf ("   ORF1: %s\n", news);
}
void orf3 (char * news) {
    printf ("   ORF3: %s\n", news);
}
void fm4 (char * news) {
    printf ("   FM4: %s\n", news);
}


int main(int argc, const char * argv[]) {
    
    printf ("Newsroom starting\n");
    
    // create your observer
    observer_t ORF1;
    observer_t ORF3;
    observer_t FM4;
    ORF1.notify = &orf1;
    ORF3.notify = &orf3;
    FM4.notify = &fm4;
    
    // create your subject
    subject_t subject;
    subject.attach = &attach;
    subject.detach = &detach;
    subject.notify = &notify;
    for (int i = 0; i < C_MAX_OBSERVER; i++)
        subject.observerCollection [i] = 0;
    subject.observerCount = 0;
    
    // add the observers
    subject.attach (&subject, &ORF1);
    subject.attach (&subject, &ORF3);
    subject.attach (&subject, &FM4);
    
    // send everybody a message
    subject.notify (&subject, "Message 1");
    
    // remove a observer
    subject.detach (&subject, &ORF3);

    // and send a new message
    subject.notify (&subject, "Message 1");
    
    printf ("Newsroom finised\n");
    
}



















