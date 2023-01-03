#include <iostream>
using namespace std;
struct processus
{
  int id;
  int priorite;
  processus *suiv;
  char etat;
};
void insertDebut(processus *&debut, int x, int y, char z)
{
  processus *nouv = new processus;
  nouv->id = x;
  nouv->priorite = y;
  nouv->suiv = debut;
  nouv->etat = z;
  debut = nouv;
}
void insertFin(processus *&debut, int x, int y, char z)
{
  if (debut == 0)
  {
    insertDebut(debut, x, y, z);
  }
  else
  {
    processus *courant = debut;
    while (courant->suiv != 0)
    {
      courant = courant->suiv;
    }
    courant->suiv = new processus;
    courant->suiv->id = x;
    courant->suiv->priorite = y;
    courant->suiv->etat = z;
    courant->suiv->suiv = 0;
  }
}
void creation(processus *&D, int n)
{
  int x, y;
  char etat;
  for (int i = 0; i < n; i++)
  {
    cout << "Enter Id[" << i + 1 << "] =";
    cin >> x;
    cout << "Enter priority[" << i + 1 << "] =";
    cin >> y;
    cout << "Enter state e for in execution, p for pending and f for finished[" << i + 1 << "] =";
    cin >> etat;

    while (etat != 'e' && etat != 'p' && etat != 'f')
    {
      if (etat == 'e' && etat == 'p' && etat == 'f')
      {
        cout << "break\n";

        break;
      }
      else
      {
        cout << "\t\t\tERROR \ne for in execution,p for pending,f for finished\n ";
        cout << "Enter state [" << i + 1 << "] =";
        cin >> etat;
      }
    }

    insertFin(D, x, y, etat);
    cout << endl;
  }
}
void afficher(processus *&D)
{
  processus *courant = D;
  if (courant == 0)
    cout << "*----------Empty list----------*\n";
  else
    while (courant != 0)
    {
      cout << "Id={" << courant->id << "}\t";
      cout << "priority={" << courant->priorite << "}\t";
      cout << "state={" << courant->etat << "}\t";
      cout << "\n";
      courant = courant->suiv;
    }
}
void maxprio(processus *&debut)
{
  processus *courant = debut;
  processus *max = debut;
  processus *pred;

  do
  {
    if (courant->priorite > max->priorite)
    {
      max = courant;
    }

    courant = courant->suiv;

  } while (courant != 0);

  if (max != debut)
  {
    courant = debut;
    pred = debut;

    while (courant->suiv != 0)
    {
      if (courant->suiv == max)
      {
        pred = courant;
        break;
      }
      else
      {
        courant = courant->suiv;
      }
    }

    // linking the previous processus of next one;
    pred->suiv = max->suiv;

    // linking the node with the head;
    max->suiv = debut;

    // puting the node as the new head;
    debut = max;
  }
}
void supprimer(processus *&debut)
{
  processus *sup;
  while (debut != 0)
  {
    sup = debut;
    debut = debut->suiv;
    delete sup;
  }
}
void InverserList(processus *&D)
{
  processus *courant = D;
  processus *l = 0;
  while (courant != 0)
  {
    insertDebut(l, courant->id, courant->priorite, courant->etat);
    courant = courant->suiv;
  }
  supprimer(D);
  D = l;
}
void suppVal(processus *&D, int val)
{
  processus *courant;
  processus *pred;
  if (D != 0 && D->priorite == val)
  {
    courant = D;
    D = D->suiv;
    delete courant;
    courant = 0;
    return;
  }
  courant = D;
  pred = courant;
  while (courant != 0)
  {
    if (courant->priorite == val)
    {
      pred->suiv = courant->suiv;
      delete courant;
      courant = 0;
    }
    else
    {
      pred = courant;
      courant = courant->suiv;
    }
  }
}
void suppetatT(processus *&D)
{
  processus *courant;
  processus *pred;
  processus *tete;
  courant = D;
  tete = D;

  while (courant != 0)
  {

    if (courant->etat == 'f')
    {
      if (courant == tete)
      {
        tete = tete->suiv;
        courant = courant->suiv;
      }
      else
      {
        pred->suiv = courant->suiv;
        courant = courant->suiv;
      }
    }
    else
    {
      pred = courant;
      courant = courant->suiv;
    }
  }
  D = tete;
}
int main()
{
  cout << "\n";
  cout << "\t\t\t\t\t\t\t-----------------------------projet ASD1-----------------------------\n";
  // Initialization des variables;
  int Nproces, M, val;
  // Lecture nombre de processus;
  cout << "Enter number of processes: ";
  cin >> Nproces;
  processus **L = new processus *[Nproces];
  for (int i = 0; i < Nproces; i++)
  {
    L[i] = 0;
    cout << "Enter the array size [" << i + 1 << "] : ";
    cin >> M;
    creation(L[i], M);
  }
  // Premier affichage;
  cout << "\n";
  cout << "\nEntered array:\n";
  for (int i = 0; i < Nproces; i++)
  {
    cout << "--------------L[" << i + 1 << "]--------------\n";
    afficher(L[i]);
  }

  // Inversion des listes
  cout << "\n";
  cout << "\nArray with reversed lists:\n";
  for (int i = 0; i < Nproces; i++)
  {
    InverserList(L[i]);
  }

  // Affichage apres inversion;
  for (int i = 0; i < Nproces; i++)
  {
    cout << "--------------L[" << i + 1 << "]--------------\n";
    afficher(L[i]);
  }

  cout << "\n";
  cout << "\nArray of ordered lists by priority:\n";
  for (int i = 0; i < Nproces; i++)
  {
    maxprio(L[i]);
    cout << "--------------L[" << i + 1 << "]--------------\n";
    afficher(L[i]);
  }
  cout << "\n";
  cout << "\nEnter the priority value to delete: ";
  cin >> val;
  for (int i = 0; i < Nproces; i++)
  {
    suppVal(L[i], val);
    cout << "--------------L[" << i + 1 << "]--------------\n";
    afficher(L[i]);
  }

  cout << endl
       << "deleting all etat T processus..." << endl;

  for (int i = 0; i < Nproces; i++)
  {
    suppetatT(L[i]);
    cout << "--------------L[" << i + 1 << "]--------------\n";
    afficher(L[i]);
  }
  cout << "\n";
  cout << "\t\t\t\t\t\t\t-----------------------------this is ELON MUSK!!!-----------------------------\n";
  for (int i = 0; i < 5; i++)
  {
    cout << "\n";
  }
  return 0;
}