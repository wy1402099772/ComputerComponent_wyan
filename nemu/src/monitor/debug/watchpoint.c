#include "monitor/watchpoint.h"
#include "monitor/expr.h"


#define NR_WP 32

static WP wp_list[NR_WP];
static WP *head, *free_;

void init_wp_list() {
	int i;
	for(i = 0; i < NR_WP - 1; i ++) {
		wp_list[i].NO = i;
		wp_list[i].next = &wp_list[i + 1];
	}
	wp_list[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_list;
}

/* TODO: Implement the functionality of watchpoint */
WP* new_wp()
{
    WP* tmp = free_;
    if(free_)
    {
        free_ = free_->next;
        tmp->next = NULL;
        return tmp;
    }
    else
    {
        printf("watch point pool is empty, free_ == NULL now!\n");
        assert(0);
    }
    return NULL;
}

void free_wp(WP *wp)
{
    WP* tmp = NULL;
    if(free_ == NULL)
    {
        free_ = wp;
        wp->next = NULL;
        return ;
    }
    for(tmp = free_; free_ -> next; tmp = tmp->next);
    tmp->next = wp;
    wp->next = NULL;
    return ;
}
