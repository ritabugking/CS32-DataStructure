

void listAll(string path, const File* f)  // two-parameter overload
{
    string tmp = "/" + f->name();
    path += tmp;
    cout << path << endl;
    if (f->files() != nullptr)  // f->files() return "A VECTOR" contains lots of file pointers, which point to subfolders or files
    {
        // f->files()->begin() let "it" points to the beginning of vector
        // usually we use v.begin(), but here f->files() is a pointer. It should be (*f->files()).begin() which is equal to f->files()->begin()
        for (vector<File*>::const_iterator it = f->files()->begin(); it != f->files()->end(); it++)
        {
            listAll(path, *it);
        }
    }
}


