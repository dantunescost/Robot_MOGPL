/* COMPILE USING:  g++ -Wall -pedantic -g -std=c++11 test.cpp graph.cpp `pkg-config --cflags --libs gtk+-3.0` -o fen*/
#include <gtk/gtk.h>
#include "graph.h"

using namespace std;

#define WINDOW_WIDTH  620
#define WINDOW_HEIGHT 620

typedef struct
{
  int xStart;
  int yStart;
  int xGoal;
  int yGoal;

  int dirStart;
  /* Nord  => 0
   *  Est   => 1
   *  Sud   => 2
   *  Ouest => 3
   */

  int n;			// Nombre de lignes du probleme
  int m;			// Nombre de colonnes du probleme 
  string chaine_res;
  int nb;

    std::vector < std::vector < bool > >grid;	// true => obstacle ; false => libre
} struct_problem;

static gboolean
draw_cb (GtkWidget * widget, cairo_t * cr, gpointer data)
{
  struct_problem *p = (struct_problem *) data;

  int case_width = 500 / ((p->n < p->m) ? p->m : p->n);

  /* Set color for background */
  cairo_set_source_rgb (cr, 1, 1, 1);
  /* fill in the background color */
  cairo_paint (cr);

  /* set color for lines */
  cairo_set_source_rgb (cr, 0.2479, 0.3183, 0.67);
  /* set the line width */
  cairo_set_line_width (cr, 1);

  /*drawing the lines of the grid (columns) */
  for (int i = 0; i <= p->m; i++)
    {
      cairo_move_to (cr, 25 + i * case_width, 25);
      cairo_line_to (cr, 25 + i * case_width, 25 + case_width * p->n);
      cairo_stroke (cr);
    }

  /*drawing the lines of the grid (rows) */
  for (int i = 0; i <= p->n; i++)
    {
      cairo_move_to (cr, 25, 25 + i * case_width);
      cairo_line_to (cr, 25 + p->m * case_width, 25 + case_width * i);
      cairo_stroke (cr);
    }

  /* set color for rectangle */
  cairo_set_source_rgb (cr, 0.4508, 0.9044, 0.92);
  /* set the line width */
  cairo_set_line_width (cr, 1);
  /*drawing the obstacles */
  for (int i = 0; i < p->n; i++)
    {
      for (int j = 0; j < p->m; j++)
	{
	  if (p->grid[i][j] == 1)
	    {
	      /* draw the rectangle */
	      cairo_rectangle (cr, 26 + j * case_width, 26 + i * case_width,
			       case_width - 2, case_width - 2);
	      /* stroke the rectangle's path with the chosen color so it's actually visible */
	      cairo_fill (cr);
	    }
	}
    }

  /* draw path */
  ifstream res (p->chaine_res);
  if (!res.is_open ())
    {
      cerr << "Échec de l'ouverture du fichier!" << endl;
    }
  else
    {
      string mot;
      for(int i=0; i<p->nb; i++)
      	getline(res,mot);
      res >> mot;
      if (mot.compare("-1") != 0)
	{
	  int x = p->xStart, x1;
	  int y = p->yStart, y1;
	  int dir = p->dirStart;
	  cairo_set_source_rgb (cr, 0., 0., 0.);
	  cairo_set_line_width (cr, 4);
	  while (x != p->xGoal || y != p->yGoal)
	    {
	      res >> mot;
	      if (mot == "D")
		{
		  dir = (dir + 1) % 4;
		}
	      else if (mot == "G")
		{
		  dir = ((4+((dir - 1) % 4))%4);
		}
	      else if (mot == "a1")
		{
		  if (dir == 0)
		    {
		      x1 = x - 1;
		      y1 = y;
		    }
		  else if (dir == 1)
		    {
		      x1 = x;
		      y1 = y + 1;
		    }
		  else if (dir == 2)
		    {
		      x1 = x + 1;
		      y1 = y;
		    }
		  else if (dir == 3)
		    {
		      x1 = x;
		      y1 = y - 1;
		    }
		  cairo_move_to (cr, 25 + y * case_width,
				 25 + x * case_width);
		  cairo_line_to (cr, 25 + y1 * case_width,
				 25 + x1 * case_width);
		  cairo_stroke (cr);
		  x = x1;
		  y = y1;
		}
	      else if (mot == "a2")
		{
		  if (dir == 0)
		    {
		      x1 = x - 2;
		      y1 = y;
		    }
		  else if (dir == 1)
		    {
		      x1 = x;
		      y1 = y + 2;
		    }
		  else if (dir == 2)
		    {
		      x1 = x + 2;
		      y1 = y;
		    }
		  else if (dir == 3)
		    {
		      x1 = x;
		      y1 = y - 2;
		    }
		  cairo_move_to (cr, 25 + y * case_width,
				 25 + x * case_width);
		  cairo_line_to (cr, 25 + y1 * case_width,
				 25 + x1 * case_width);
		  cairo_stroke (cr);
		  x = x1;
		  y = y1;
		}
	      else if (mot == "a3")
		{
		  if (dir == 0)
		    {
		      x1 = x - 3;
		      y1 = y;
		    }
		  else if (dir == 1)
		    {
		      x1 = x;
		      y1 = y + 3;
		    }
		  else if (dir == 2)
		    {
		      x1 = x + 3;
		      y1 = y;
		    }
		  else if (dir == 3)
		    {
		      x1 = x;
		      y1 = y - 3;
		    }
		  cairo_move_to (cr, 25 + y * case_width,
				 25 + x * case_width);
		  cairo_line_to (cr, 25 + y1 * case_width,
				 25 + x1 * case_width);
		  cairo_stroke (cr);
		  x = x1;
		  y = y1;
		}
	    }
	}
      else
	{
	  cout << "Pas de chemin trouvé!" << endl;
	}
    }

    /* draw goal circle */
  cairo_set_source_rgb (cr, 1., 0., 0.);
  cairo_set_line_width (cr, 2);
  cairo_arc (cr, 25 + p->yGoal * case_width, 25 + p->xGoal * case_width,
	     0.25 * case_width, 0, 2 * G_PI);
  cairo_fill (cr);
  /* draw start circle */
  cairo_set_source_rgb (cr, 0., 1., 0.);
  cairo_arc (cr, 25 + p->yStart * case_width, 25 + p->xStart * case_width,
	     0.25 * case_width, 0, 2 * G_PI);
  cairo_fill (cr);
  cairo_set_source_rgb (cr, 0., 0., 0.);
  /* draw start direction arrow */
  switch (p->dirStart)
    {
    case 0:
      cairo_move_to (cr, 25 + p->yStart * case_width - 0.1 * case_width,
		     25 + p->xStart * case_width - 0.25 * case_width);
      cairo_line_to (cr, 25 + p->yStart * case_width,
		     25 + p->xStart * case_width - 0.7 * case_width);
      cairo_line_to (cr, 25 + p->yStart * case_width + 0.1 * case_width,
		     25 + p->xStart * case_width - 0.25 * case_width);
      cairo_close_path (cr);
      cairo_fill (cr);
      break;
    case 1:
      cairo_move_to (cr, 25 + p->yStart * case_width + 0.25 * case_width,
		     25 + p->xStart * case_width - 0.1 * case_width);
      cairo_line_to (cr, 25 + p->yStart * case_width + case_width * 0.7,
		     25 + p->xStart * case_width);
      cairo_line_to (cr, 25 + p->yStart * case_width + 0.25 * case_width,
		     25 + p->xStart * case_width + 0.1 * case_width);
      cairo_close_path (cr);
      cairo_fill (cr);
      break;
    case 2:
      cairo_move_to (cr, 25 + p->yStart * case_width - 0.1 * case_width,
		     25 + p->xStart * case_width + 0.25 * case_width);
      cairo_line_to (cr, 25 + p->yStart * case_width,
		     25 + p->xStart * case_width + 0.7 * case_width);
      cairo_line_to (cr, 25 + p->yStart * case_width + 0.1 * case_width,
		     25 + p->xStart * case_width + 0.25 * case_width);
      cairo_close_path (cr);
      cairo_fill (cr);
      break;
    case 3:
      cairo_move_to (cr, 25 + p->yStart * case_width - 0.25 * case_width,
		     25 + p->xStart * case_width - 0.1 * case_width);
      cairo_line_to (cr, 25 + p->yStart * case_width - case_width * 0.7,
		     25 + p->xStart * case_width);
      cairo_line_to (cr, 25 + p->yStart * case_width - 0.25 * case_width,
		     25 + p->xStart * case_width + 0.1 * case_width);
      cairo_close_path (cr);
      cairo_fill (cr);
      break;
    default:
      cairo_fill (cr);
    }
  return FALSE;
}


int
main (int argc, char *argv[])
{
  string fichier;
  int nbprob = 0;
  bool firstTime = true;
  cout << "Entrez le nom du fichier: " << endl;
  cin >> fichier;
  struct_problem sp;
  graph solver = graph ();
  vector<problem> prob;

  gtk_init (&argc, &argv);
  while(1){
  if(solver.readProblems (fichier)){
  	if(firstTime)
  	{
  		prob = solver.getProblems();
  		solver.solveAllProblems();
  		firstTime = false;
  	}
  	cout << "Entrez le numéro du problème: " << endl;
  	cin >> nbprob;
  	if(nbprob == -1)
  		break;
	sp.xStart = prob[nbprob].xStart;
	sp.yStart = prob[nbprob].yStart;
	sp.xGoal = prob[nbprob].xGoal;
	sp.yGoal = prob[nbprob].yGoal;
	sp.dirStart = prob[nbprob].dirStart;
	sp.n = prob[nbprob].n;
	sp.m = prob[nbprob].m;
	sp.chaine_res = fichier + "Results";
	sp.grid = prob[nbprob].grid;
	sp.nb = nbprob;

	GtkWidget *window;
	GtkWidget *da, *container;

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "La balade du Robot...");
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	container = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (window), container);
	gtk_widget_set_size_request (container, WINDOW_WIDTH, WINDOW_HEIGHT);

	da = gtk_drawing_area_new ();
	gtk_widget_set_size_request (da, 550, 550);
	g_signal_connect (da, "draw", G_CALLBACK (draw_cb), &sp);

	gtk_fixed_put (GTK_FIXED (container), da, 30, 30);
	gtk_widget_show (container);
	gtk_widget_show (da);
	gtk_widget_show (window);
	  
	gtk_main ();
  }


  } // while
  prob.clear();
  return 0;
}
