Student* p = new Student(0,0);
    for (size_t i = 0; i < 3; i++)
    {
        p = head;
        cout << "[num=" << p->Num << ",score=" << p->Score << "]" << endl; 
        p=p->Next;   
        //std::cout << std::format("[num={},score={}]", num, score) << std::endl;
        /* code */
    }
    
    /* code */