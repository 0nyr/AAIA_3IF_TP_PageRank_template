#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// DiGraph representation using adjacency lists
typedef struct {
    int n; // number of vertices in the graph
    int* nbSucc; // for each 0<=i<n, nbSucc[i] = number of successors of i
    int** succ; // for each 0<=i<n and each 0<=j<nbSucc[i], succ[i][j]=jth successor of i
} DiGraph;

/**
 * Read a DiGraph from a file.
 * 
 * A DiGraph is a directed graph that is a modelization
 * of a web page network. Each vertex is a web page and
 * each edge is a hyperlink from one page to another.
*/
DiGraph* readDigraph(FILE *fp) {
    // return the DiGraph contained in file fp
    DiGraph *g = (DiGraph*)malloc(sizeof(DiGraph));
    if (fscanf(fp, "%d\n", &(g->n)) != 1 || g->n <= 0) {
        printf("erreur de lecture du fichier\n");
        exit(1);
    }
    g->nbSucc = (int*)malloc(g->n*sizeof(int));
    g->succ = (int**)malloc(g->n*sizeof(int*));
    int succ[g->n];
    for (int i=0; i<g->n; i++) {
        g->nbSucc[i] = 0;
        while (1) {
            if (fscanf(fp, "%d", &(succ[g->nbSucc[i]])) != 1 || succ[g->nbSucc[i]] >= g->n) {
                printf("erreur de lecture du fichier\n");
                exit(1);
            }
            if (succ[g->nbSucc[i]]<0) break;
            g->nbSucc[i]++;
        };
        g->succ[i] = (int*)malloc(g->nbSucc[i]*sizeof(int));
        memcpy(g->succ[i], succ, g->nbSucc[i]*sizeof(int));
    }
    return g;
}

/**
 * Print a DiGraph to the standard output.
*/
void printDigraph(DiGraph *g) {
    printf("Number of vertices: %d\n", g->n);

    // For each vertex of g, display the list of its successors
    for (int i=0; i<g->n; i++) {
        printf("Vertex %d has %d successors: ", i, g->nbSucc[i]);
        for (int j=0; j<g->nbSucc[i]; j++)
            printf("%d ", g->succ[i][j]);
        printf("\n");
    }
}

/**
 * Scores of the PageRank algorithm.
 * 
 * Each web page has a score that is computed by the PageRank algorithm.
*/
typedef struct {
    int k; // step number of the PageRank algorithm
    double* scores; // for each 0<=i<n, scores[i] = score
} Scores;

// Print the scores of the PageRank algorithm
void printScores(Scores* scores_at_k, int n) {
    printf("Scores at step %d: [", scores_at_k->k);
    for (int j=0; j<n; j++) {
        printf("%f", scores_at_k->scores[j]);
        if (j<n-1) printf(", ");
    }

    double sum = 0;
    for (int j=0; j<n; j++) {
        sum += scores_at_k->scores[j];
    }
    printf("] (sum: %f)\n", sum);
}

/* Print score like so:
Scores at step 0: [0.166667, 0.166667, 0.166667, 0.166667, 0.166667, 0.166667]
Scores at step 1: [0.027778, 0.055556, 0.027778, 0.319444, 0.291667, 0.277778]
Scores at step 2: [0.009259, 0.023148, 0.013889, 0.423611, 0.224537, 0.305556]
*/
void printScoresArray(Scores** scores, int lastK, int n) {
    for (int i=0; i<=lastK; i++) {
        printScores(scores[i], n);
    }
}

Scores** pagerank(DiGraph* g, int k) {
    // return the scores of the PageRank algorithm up to step k
    Scores** scores = (Scores**)malloc((k+1)*sizeof(Scores*));

    // initial scores at step 0
    scores[0] = (Scores*)malloc(sizeof(Scores));
    scores[0]->k = 0;
    scores[0]->scores = (double*)malloc(g->n*sizeof(double));
    for (int j=0; j<g->n; j++) {
        // initial transition probabilities are uniform
        scores[0]->scores[j] = 1.0/(double)g->n;
    }
        
    // step k >= 1
    for (int i=1; i<=k; i++) {
        // IMPLEMENT YOUR SOLUTION HERE
    }
    return scores;
}

int main() {
    // # Exercice 1: Load a first example graph
    printf("\nExercice 1:\n");

    FILE* fp  = fopen("res/example_1.txt", "r");
    DiGraph* g = readDigraph(fp);
    fclose(fp);

    printDigraph(g);

    // Compute the PageRank scores of the first example graph
    int k = 4;
    Scores** scores = pagerank(g, k);
    printScoresArray(scores, k, g->n);

    return 0;
}
