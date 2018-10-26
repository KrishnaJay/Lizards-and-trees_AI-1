#include < iostream > 
#include < fstream > 
#include < vector > 
#include < string >

using namespace std;

struct pos 
{
  int row;
  int col;

}
p[1000], t[1000];

class mat 
{
  public:
    int liz;
	int n;
	int tr;
};

bool solution_without_trees(mat m1, int rc) {
  
  if (m1.liz == rc)
    return true;

  for (int col = 0; col < m1.n; col++) {
    bool sol = true;
    for (int li = 0; li < rc; li++) {
      if ((p[li].col == col) or(p[li].row + p[li].col == rc + col) or(p[li].row - p[li].col == rc - col)) {
        sol = false;
        break;
      }

    }
    if (sol) {

      
      p[rc].row = rc;

      p[rc].col = col;

      if (solution_without_trees(m1, rc + 1)) {
        return true;
      }
    }
  }
  return false;
}

bool notreedetected(int tree, int rr, int cc) {
  int temp = 0;
  for (int j = 0; j < tree; j++)
    if (rr == t[j].row and cc == t[j].col)
      temp++;

  if (temp > 0)
    return false;
  else return true;

}

bool solutiont(mat m1, int count) {

  
  if (m1.liz == count)
    return true;

  bool sol = false;
  for (int rc = 0; rc < m1.n; rc++) {
    for (int col = 0; col < m1.n; col++) {
      if (notreedetected(m1.tr, rc, col)) { 
        sol = true;
        for (int o = 0; o < count; o++)
          if ((p[o].row == rc and p[o].col == col)) 
        {
          sol = false;
          goto here;
        }
      } else {
        sol = false;
        goto here;
      }

      for (int li = 0; li < count; li++) {
        if ((p[li].col == col) or(p[li].row == rc) or(p[li].row + p[li].col == rc + col) or(p[li].row - p[li].col == rc - col)) {
          int temp = 0;
          for (int x = 0; x < m1.tr; x++)
            if ((t[x].col == col and p[li].col == col and p[li].row < t[x].row and t[x].row < rc) or(t[x].row == rc and p[li].row == rc and p[li].col < t[x].col and t[x].col < col) or(t[x].row + t[x].col == rc + col and p[li].row + p[li].col == rc + col and p[li].row < t[x].row and t[x].row < rc and p[li].col < t[x].col and t[x].col < col) or(t[x].row - t[x].col == rc - col and p[li].row - p[li].col == rc - col and p[li].row < t[x].row and t[x].row < rc and p[li].col < t[x].col and t[x].col < col))
              temp++;

          if (temp > 0)
            sol = true;

          else {
            sol = false;
            break;
          }

        }

      }
      here: if (sol) {

        
        p[count].row = rc;

        p[count].col = col;

        if (solutiont(m1, count + 1)) {
          return true;
        }

      }
    }
  }
  return false;
}

int main() {
  int n, l, i, j;
  int k = 0;
  bool tree_is_there = false;
  string str;
  ifstream myReadFile;
  ofstream myWriteFile;
  myReadFile.open("input.txt");
  myWriteFile.open("output.txt");
  myReadFile >> str;
  myReadFile >> n;
  myReadFile >> l;
  
  char c;
  mat m;
  m.n = n;
  m.liz = l;

  bool flag;

  vector < vector < int > > matrix(n, vector < int > (n));
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      myReadFile >> c;
      matrix[i][j] = c - '0';

    }
    cout << endl;
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (matrix[i][j] == 2) {
        tree_is_there = true;
        t[k].row = i;
        t[k].col = j;
        k++;

      }

    }
  }

  m.tr = k;
  
  if (str == "DFS" || str == "SA" || str == "BFS") {
    if (!tree_is_there) { //cout<<"calling sol";
      flag = solution_without_trees(m, 0);
    } else { 
      flag = solutiont(m, 0);
    }

    if (!flag)
      myWriteFile << "FAIL";
    else {
      myWriteFile << "OK \n";

      for (int i = 0; i < m.liz; i++)
        matrix[p[i].row][p[i].col] = 1;

      for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
          myWriteFile << matrix[i][j];

        }
        if (i != m.n - 1)
          myWriteFile << endl;
      }
    }
  }
  myReadFile.close();
  myWriteFile.close();

  return 0;
}