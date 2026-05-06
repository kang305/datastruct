#include "LinkLoop.h"
#include "Joseph.h"
#include<stdio.h>
void test01() {
    LinkLoop link_loop;
    initLinkLoop(&link_loop);
    for(int i=0;i<10;i++) {
        //insertLinkLoopHeader(&link_loop,i+10);
        insertLinkLoopRear(&link_loop,i+100);
    }
    showLinkLoop(&link_loop);
    deleteLinkLoop(&link_loop,110);
    showLinkLoop(&link_loop);
    deleteAllLinkLoop(&link_loop);
}
 void JosephGameTest() {
    JosephHeader game1={NULL,NULL};
    initJoseph(&game1,5);
    showJoseph(&game1);
    startJoseph(&game1,2);
}
int main() {
  //test01();
    JosephGameTest();
    return 0;
}