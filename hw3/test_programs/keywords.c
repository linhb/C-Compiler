int keywordTest(void)
{
    int i;
    for ( i = 0; i < 10; i++ )
      {
        continue;
      }
    for ( ;; )
      {
        break;
        goto label; 
      }
    return 1;
    do
      {
        i=2;
        break;
        continue;
        goto label; 
      }while(0);

    goto label; 
    
    do
      {
        i=2;
        break;
        continue;
      }while(i);
    
    while (1)
      {
        break;
        continue;
        i = 32;
        goto label; 
      }
    while (i)
      {
        i = 32;
        break;
        continue;
        return i;
      }
 label1: 

    for ( ;; )
      {
        if ( i < i )
	  {
            goto label; 
	  }
        else if ( i > i )
	  {
            break;
	  }
        else
	  {
            continue;
	  }
      }
    return 1;
}

