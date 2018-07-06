
void removeBad(list<Movie*>& li)
{
    list<Movie*>::iterator it = li.begin();
    while(it != li.end())
    {
        if ((*it)->rating() < 50)  // (*it)
        {
            delete  (*it); // delete the pointer which points to certain movie
            li.erase(it++);
        }
        else
        {
            it++;
        }
    }
}

