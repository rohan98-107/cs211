unsigned int btoi(unsigned long int x)
{
    unsigned long int result = 0;
    unsigned long int temp = x;
    int power = 1;
    while( temp )
    {
        unsigned long int temp2 = temp%10;
        temp /= 10;
        result += temp2*power;
        power *= 2;
    }
    
    return result;
}

Line *enqueue(Line *head, Line *new)
{
    Line *ptr = head;
    if(ptr == NULL)
        ptr = new;
    else
    {
        new->next = ptr;
        ptr = new;
    }
    
    return ptr;
}

Line *dequeue(Line* head)
{
    Line* ptr = head->next;
    Line* prev = head;
    
    if(ptr == NULL)
    {
        head = NULL;
        return head;
    }
    
    while(ptr->next != NULL)
    {
        ptr = ptr->next;
        prev = prev->next;
    }
    
    prev->next = NULL;
    
    return head;
}
