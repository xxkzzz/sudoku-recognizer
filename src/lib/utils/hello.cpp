#include <string>
#include <vector>
using namespace std; // Or using std::string;

#include "../hello.h"
#include <sys/stat.h>

int isDirectory(const char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

vector<string> splitPath(string path)
{
    stringstream ss(path);
    vector<string> result;

    while (ss.good())
    {
        string substr;
        getline(ss, substr, '/');
        result.push_back(substr);
    }

    return result;
}

string joinPath(vector<string> strs)
{
    stringstream ss;

    for (int i = 0; i < strs.size(); i++)
    {
        ss << strs[i];
        if (i != strs.size() - 1)
        {
            ss << "/";
        }
    }

    return ss.str();
}

string getMyProjectRoot(string projectRootName, string path)
{
    vector<string> strs(splitPath(path));

    string last = strs[strs.size() - 1];
    if (last == projectRootName)
    {
        return path;
    }
    else
    {
        strs.pop_back();

        if (strs.empty())
        {
            throw "could not find project root (in function getMyProjectRoot)";
        }
        return getMyProjectRoot(projectRootName, joinPath(strs));
    }
}

int main(int argc, char **argv)
{
    string projectRootFolderName = "sudoku";
    // vector<string> strs(splitPath("/keep/Repo/USELESS/_sandbox/cpp/stng-cpp/sudoku/build"));

    // for (int i = 0; i < strs.size(); i++)
    // {
    //     cout << strs[i] << endl;
    // }

    //     cout << joinPath(strs) << endl;

    // string result = getMyProjectRoot(projectRootFolderName, "/keep/Repo/USELESS/_sandbox/cpp/learning-cpp/sudoku/build");
    // cout << result << endl;

    if (isDirectory("/keep/Repo/USELESS/_sandbox/cpp/learning-cpp/sudoku/build"))
    {
        cout << "dir" << endl;
    }
    else
    {
        cout << "file" << endl;
    }

    return 0;
}