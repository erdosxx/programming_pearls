#ifndef PROGRAMMING_PEARLS_COLUMN15_H
#define PROGRAMMING_PEARLS_COLUMN15_H

#include <set>
#include <string>
#include <stdlib.h>

using namespace std;

class StringSetSTL {
private:
	set<string> S;
public:
	StringSetSTL() {}

	int size() {
        return S.size();
    }

	void insert(string t) {
        S.insert(t);
    }

	void report(string *v) {
		int j = 0;
		set<string>::iterator i;

		for (i = S.begin(); i != S.end(); ++i)
			v[j++] = *i;
	}
};

class countWord {
private:

    struct node {
        char *word;
        int count;
        node* next;
    };

    typedef node* nodeptr;

    enum {NHASH=29989, MULT=31, NODEGROUP=1000, CHARGROUP=10000};

    unsigned int hash(char *p) {
        unsigned int h = 0;

        for ( ; *p; p++)
            h = MULT * h + *p;

        return h % NHASH;
    }

    int nodesleft;
    nodeptr freenode;

    nodeptr nmalloc() {
        if (nodesleft == 0) {
            freenode = (nodeptr) malloc(NODEGROUP * sizeof(node));
            nodesleft = NODEGROUP;
        }

        nodesleft--;
        return freenode++;
    }

    int charsleft;
    char *freechar;

    char *smalloc(int n) {
        if (charsleft < n) {
            freechar = (char*) malloc(n+CHARGROUP);
            charsleft += n+CHARGROUP;
        }

        charsleft -= n;
        freechar += n;
        return freechar - n;
    }

    nodeptr bin[NHASH];

public:
    countWord(): nodesleft(0), charsleft(0) {
        for (int i = 0; i < NHASH; i++)
            bin[i] = NULL;
    }

    void incword(char *s) {
        nodeptr p;
        int h = hash(s);

        for (p = bin[h]; p != NULL; p = p->next)
            if (strcmp(s, p->word) == 0) {
                (p->count)++;
                return;
            }

        // Add new entry in front of hash table.
        p = nmalloc();
        p->count = 1;
        p->word = smalloc(strlen(s)+1);
        strcpy(p->word, s);
        p->next = bin[h];
        bin[h] = p;
    }

    int findcount(char *s) {
        nodeptr p;
        int h = hash(s);

        for (p = bin[h]; p != NULL; p = p->next)
            if (strcmp(s, p->word) == 0) {
                return p->count;
            }

        return 0;
    }
};

class longDupSubStr {
private:
    /*
    static int pstrcmp(const void *p, const void *q) {
        return strcmp( *p, *q);
    }
    */

    static int pstrcmp(const void *p, const void *q) {
        return strcmp(*(const char**)p, *(const char**)q );
    }

    int comlen(char *p, char *q) {
        int i = 0;
        while (*p && (*p++ == *q++))
            i++;
        return i;
    }

    enum {MAXN=50000};
    char c[MAXN];
    char* a[MAXN];

    int n;
    int maxi;
    int maxlen;

public:
    longDupSubStr(): n(0), maxlen(-1) {}

    void getInputStr(char* ch) {
        strcpy(c, ch);

        n = strlen(ch);

        for(int i=0; i< n; i++) {
            a[i] = &c[i];
        }

        c[n] = 0;  // NULL
    }

    int get_size() {
        return n;
    }

    char* get_char(int i) {
        return a[i];
    }

    void sortarray() {
        qsort(a, n, sizeof(char *), pstrcmp);
    }

    int get_maxi(){
        return maxi;
    }

    int get_maxlen(){
        return maxlen;
    }

    void getMaxSubStr(int occur, char* outstr) {
        qsort(a, n, sizeof(char *), pstrcmp);
        for (int i = 0; i < n-occur; i++)
            if (comlen(a[i], a[i+occur]) > maxlen) {
                maxlen = comlen(a[i], a[i+occur]);
                maxi = i;
            }

        strncpy(outstr, a[maxi], maxlen);
    }
};

class markov {
private:
    enum {MAXINPUTSIZE=43000, MAXWORDSIZE=8000, NHASH=499979, MULT=31 };
    char* inputchars;
    char *word[MAXWORDSIZE];
    char *gen_word[MAXWORDSIZE];
    int nword;
    int k;  //order-k
    char* phrase;
    int wordsleft;
    int num_gen_word;
    int bin[NHASH];
    int next[MAXWORDSIZE];

    static int wordncmp(const char *p, const char* q) {
        //TODO: How can we add k gram in sort fouction?
        //int n = k;
        int n = 2;
        for ( ; *p == *q; p++, q++)
            if (*p == 0 && --n == 0)
                return 0;
        return *p - *q;
    }

    static int sortcmp(const void *p, const void *q) {
        return wordncmp(*(const char**)p, *(const char**)q);
    }

    char *skip(char *p, int n) {
        for ( ; n > 0; p++)
            if (*p == 0)
                n--;
        return p;
    }

    unsigned int hash(char *ptr) {
        unsigned int h = 0;
        char *p = ptr;
        int n;

        for (n = k; n > 0; p++) {
            h = MULT * h + *p;
            if (*p == 0)
                n--;
        }

        return h % NHASH;
    }

public:
    markov(char* inputstr, int order): nword(0), k(order), num_gen_word(0), inputchars(inputstr){
        word[0] = inputstr;

        int wordlen =0;
        int cumwordlen=0;

        // continuously read inputstr
        while (sscanf(inputstr + cumwordlen, "%s", word[nword]) != EOF) {
            wordlen = strlen(word[nword]) + 1;
            cumwordlen += wordlen;
            word[nword+1] = word[nword] + wordlen;
            nword++;
        }

        for (int i = 0; i < k; i++)
            word[nword][i] = 0;
    }

    void sort() {
        qsort(word, nword, sizeof(word[0]), sortcmp);
    }

    int getnword() {
        return nword;
    }

    char* getword(int i) {
        return word[i];
    }

    int get_num_gen_word(){
        return num_gen_word;
    }

    char* get_gen_word(int i) {
        return gen_word[i];
    }

    void report_gen_text(){
        printf("\n");
        for(int i=0; i < num_gen_word; i++) {
            printf("%s ", gen_word[i]);
        }
        printf("\n");
    }

    void gen_random_text_by_hash(int num_wordgen){
        for (int i = 0; i < k; i++) {
            gen_word[num_gen_word++] = word[i];
        }

        wordsleft = num_wordgen;

        for (int i = 0; i < NHASH; i++)
            bin[i] = -1;

        for (int i = 0; i <= nword - k; i++) { /* check */
            /* insert new entry in front of hash */
            int j = hash(word[i]);
            next[i] = bin[j];
            bin[j] = i;
        }

        phrase = inputchars;

        char* p;
        for ( ; wordsleft > 0; wordsleft--) {
            int i = 0;

            for (int j = bin[hash(phrase)]; j >= 0; j = next[j])
                if ((wordncmp(phrase, word[j]) == 0)
                    && (rand() % (++i) == 0))
                    p = word[j];

            phrase = skip(p, 1);

            if (strlen(skip(phrase, k-1)) == 0)
                break;

            gen_word[num_gen_word++] = skip(phrase, k-1);
        }

    }

    void gen_random_text_by_bin_search(int num_wordgen){
        for (int i = 0; i < k; i++) {
            gen_word[num_gen_word++] = word[i];
        }

        wordsleft = num_wordgen;

        qsort(word, nword, sizeof(word[0]), sortcmp);

        phrase = inputchars;

        int l, u, m;
        char* p;

        for ( ; wordsleft > 0; wordsleft--) {
            l = -1;
            u = nword;

            while (l+1 != u) {
                m = (l + u) / 2;
                if (wordncmp(word[m], phrase) < 0)
                    l = m;
                else
                    u = m;
            }

            for (int i = 0; wordncmp(phrase, word[u+i]) == 0; i++)
                if (rand() % (i+1) == 0)
                    p = word[u+i];

            phrase = skip(p, 1);

            if (strlen(skip(phrase, k-1)) == 0)
                break;

            gen_word[num_gen_word++] = skip(phrase, k-1);
            //printf("%s\n", skip(phrase, k-1));
        }

    }

};

class markovlet {
private:
    enum {MAXSIZE=5000000};
    char outputchar[MAXSIZE];
    int inputlen;
    int maxlen;
    int order_k;
    char* inputchars;

public:
    markovlet(char* input, int maxgenlen, int k): maxlen(maxgenlen), order_k(k), inputchars(input){
        inputlen= strlen(inputchars) + 1;
    }

    void gen_random_chars(){
        char *p, *nextp, *q;
        int selectchar;

        p = inputchars;
        srand(1);

        // init outputchar with first k letters.
        strncpy(outputchar, inputchars, order_k);

        int eqsofar;
        for (int j = maxlen; j > 0; j--) {
            eqsofar = 0;

            int i;
            for (q = inputchars; q < inputchars + inputlen - order_k + 1; q++) {
                for (i = 0; i < order_k && *(p+i) == *(q+i); i++)
                    ;
                if (i == order_k)
                if (rand() % ++eqsofar == 0)
                    nextp = q;
            }

            selectchar = *(nextp+order_k);

            if (selectchar == 0)
                break;

            //putchar(c);
            strcat(outputchar, (char*) &selectchar);
            p = nextp+1;
        }
    }

    void report_gen_chars(){
        printf("\n");
        printf("%s\n", outputchar);
    }

    char* get_outputchar(){
        return outputchar;
    }
};

#endif //PROGRAMMING_PEARLS_COLUMN15_H
