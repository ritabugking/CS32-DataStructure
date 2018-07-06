

void removeOdds(vector<int>& v)
{
    for (vector<int>::iterator it = v.begin(); it!=v.end();)
    {
        if (*it % 2 == 1)
        {
            it = v.erase(it); // point to the next item if the current item was erased
        }
        else
        {
            ++it; // if no erase happen, increment the iterator by one
        }
    }
}


