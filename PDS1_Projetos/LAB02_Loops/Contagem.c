#include <stdio.h>
int main()
{
    printf("233\n");
    for (int i = 234; i < 458; i++)
    {
        if (i < 301)
        {
            i += 4;
            printf("%d\n", i);
        }
        else if (i < 401)
        {
            i += 2;
            printf("%d\n", i);
        }
        else if (i < 500)
        {
            i += 4;
            printf("%d\n", i);
        }
    }

    return 0;
}
