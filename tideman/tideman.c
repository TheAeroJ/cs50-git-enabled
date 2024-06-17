#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
int margins[MAX * (MAX - 1) / 2][2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void sort_lists(int mov[][2], int l, int r);
void merge_lists(int mov[][2], int start, int med, int end);
bool cycle_finder(bool graph[candidate_count][candidate_count], int vertex, bool visited[candidate_count], bool recStack[candidate_count]);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference - instantiate as an empty array w/ size = total candidates
        int ranks_base = candidate_count + 1;
        int ranks[candidate_count];
        for (int count = 0; count < candidate_count; count++)
        {
            ranks[count] = ranks_base;
        }

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Check the validity of a vote - that's ALL
bool vote(int rank, string name, int ranks[])
{
    // Assign the candidate ID associated with the input `name` to ranks[rank] and return true if success
        // Check whether the `name` is a valid candidate
            // Return False if not
        // Get the ID of the valid candidate
        // Check to see whether that ID appears anywhere in the ranks[] array
            // Return False if so
        // Assign

    // Check whether 'name' is a valid candidate and, if so, return its candidate_id
    for (int i = 0; i < candidate_count; i++)
    {
        // Check to see whether the submitted name is one of the candidates
        //printf("Checking validity of candidate %s against %s...\n", name, candidates[i]);
        if (strcasecmp(name, candidates[i]) == 0)
        {
            // printf("%s is a valid candidate! \n", name);
            // Get the candidate's ID if valid
            int candidate_id = i;
            // Check to see whether this candidate_id already appears in ranks; return false if so
            for (int j = 0; j < candidate_count; j++)
            {
                if (ranks[j] == candidate_id)
                {
                    // Exit function w/ false because this isn't a valid vote
                    //printf("Voter has already voted for %s!\n", name);
                    return false;
                }
            }
            // Update ranks array with name, since we have checked our two validity conditions. Return true.
            ranks[rank] = candidate_id;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Update the preferences array based on the contents of the input ranks[]
    // REMEMBER: ranks[] is an array of ints mapping to the candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        // Iterate through ranks[] - candidates are in order of preference
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Because j is "after" i, we know that this voter prefers candidates[ranks[i]] over candidates[ranks[j]]
            // Need to add one to the value of preferences[ranks[i]][ranks[j]]
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Iterate through 'preferences' 2D Array
    // Compare preference[i][j] to preference[j][i]
        // If [i][j] is greater ->
            // create pair where winner = i and loser = j;
            // Increase pair_count by 1
            // capture Margin of victory?
        // If [j][i] is greater
            // Create pair where winner = j and loser = i
            // Increase pair_count by 1
            // Capture Margin of victory for ranking?
        // Otherwise
            // Just keep going
    // printf("Adding pairs...\n");
    int pair_index = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // NOTE: that when doing this comparison, i and j will necessarily be candidate IDs
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_index].winner = i;
                pairs[pair_index].loser = j;
                margins[pair_index][0] = preferences[i][j] - preferences[j][i];
                margins[pair_index][1] = pair_index;
                pair_index++;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Check the margin-of-victory of all pairs
    sort_lists(margins, 0, pair_count - 1);
    // Take the margins array and use it to set the pairs array to the proper order
    pair pairs_tmp[pair_count];
    for (int i = 0; i > pair_count; i++)
    {
        pairs_tmp[i] = pairs[margins[pair_count - i][1]];
    }
    for (int j = 0; j < pair_count; j++)
    {
        pairs[j] = pairs_tmp[j];
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Iterate through the sorted list of pairs from highest to lowest
    // At each pair, check to see whether adding the proposed edge would create a cycle
        // If no, flip that item in the 'locked' array to TRUE
        // If yes, move on to the next pair
    // Continue until all pairs have been exhausted
    // printf("Locking pairs...\n");
    for (int i = 0; i < pair_count; i++)
    {
        // Create a working copy of the locked graph
        // For the current pairing pairs[i] set locked_tmp TRUE at [winner][loser]
        // Feed the cycle_finder the current locked graph with the proposed edge added
            // if it returns TRUE then do nothing
            // Else add the edge to the graph
        bool locked_tmp[candidate_count][candidate_count];
        locked_tmp[pairs[i].winner][pairs[i].loser] = true;
        // Create empty visited[] and recStack[] arrays for the Cycle Finder to use
        bool visited[candidate_count];
        bool recStack[candidate_count];
        for (int j = 0; j < candidate_count; j++)
        {
            visited[j] = false;
            recStack[j] = false;
        }
        if (!cycle_finder(locked_tmp, pairs[i].winner, visited, recStack))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Find origin of the graph...which is to say the vertex with nothing pointing to it
    // So...for any given vertex v...we want to know that in the column of locked[i][j] j = v such that for all i locked[i][v] = false
    for (int i = 0; i < candidate_count; i++)
    {
        int vertices_pointing_to_i = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                vertices_pointing_to_i++;
            }
        }
        if (vertices_pointing_to_i == 0)
        {
            printf("%s is the winner!\n", candidates[i]);
        }

    }
    return;
}

void sort_lists(int mov[][2], int l, int r)
{
    // printf("Sorting list of length %i\n", pair_count);
    if (l < r)
    {
        int m = (l + r) / 2;
        // printf("Sort sublist from %i to %i\n", l, m);
        sort_lists(mov, l, m);
        // printf("Sort sublist from %i to %i\n", m + 1, r);
        sort_lists(mov, m + 1, r);
        merge_lists(mov, l, m, r);
    }
    else
    {
        return;
    }
}

void merge_lists(int mov[][2], int start, int med, int end)
{
    // printf("Merging list...\n");
    int i, j, k;
    int a1 = med - start + 1;
    int a2 = end - med;

    int left[a1][2];
    int right[a2][2];

    // Copy the original array into the two half arrays
    for (i = 0; i < a1; i++)
    {
        left[i][0] = mov[start + i][0];
        left[i][1] = mov[start + i][1];
    }
    for (j = 0; j < a2; j++)
    {
        right[j][0] = mov[med + 1 + j][0];
        right[j][1] = mov[med + 1 + j][1];
    }

    // Merge the two halves back together
    i = 0;
    j = 0;
    k = start;

    while (i < a1 && j < a2)
    {
        if (left[i][0] <= right[j][0])
        {
            mov[k][0] = left[i][0];
            mov[k][1] = left[i][1];
            i++;
        }
        else
        {
            mov[k][0] = right[j][0];
            mov[k][1] = right[j][1];
            j++;
        }
        k++;
    }

    while (i < a1)
    {
        mov[k][0] = left[i][0];
        mov[k][1] = left[i][1];
        i++;
        k++;
    }
    while (j < a2)
    {
        mov[k][0] = right[j][0];
        mov[k][1] = right[j][1];
        j++;
        k++;
    }
}

bool cycle_finder(bool graph[candidate_count][candidate_count], int v, bool visited[candidate_count], bool recStack[candidate_count])
{
    // printf("Checking for cycle...\n");
    // Given the current vertex (i), visited array, and recStack (Recursion Stack):
        // Set visited[i] = TRUE
        // Set recStack[i] = TRUE
        // Iterate through the whole "column" (j) to find TRUE values (i.e. vertices to which have an edge pointed from current vertex)
            // For each TRUE value j:
                // check whether j is in visited[] - if yes, return TRUE
                // else
                    // Call cycle_finder(graph[][], j, visited[], recStack[])
    visited[v] = true;
    recStack[v] = true;
    for (int j = 0; j < candidate_count; j++)
    {
        // Check whether there is an edge from v to j (i.e. j is adjacent to v)
        if (graph[v][j])
        {
            if (!visited[j])
            // We haven't already visited the vertex at j; so go investigate it
            {
                // Go to that vertex, see whether the cycle finder evaluates to true
                if (cycle_finder(graph, j, visited, recStack))
                {
                    return true;
                }
            }
            else if (recStack[j])
            {
                return true;
            }
        }
    }
    recStack[v] = false;
    return false;

}
