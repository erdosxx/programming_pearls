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

	void insert(string value) {
        S.insert(value);
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
        if (charsleft < n) {     //sizeof(char) = 1
            freechar = (char*) malloc((n+CHARGROUP)* sizeof(char));
            charsleft += n+CHARGROUP;
        }

        charsleft -= n;
        freechar += n;
        return freechar - n;
    }

    nodeptr bin[NHASH];

    void add_node_in_front_of_hash_table(const char *s, nodeptr p, int hash_val) {
        p = nmalloc();
        p->count = 1;
        p->word = smalloc(strlen(s) + 1);
        strcpy(p->word, s);
        p->next = bin[hash_val];
        bin[hash_val] = p;
    }

public:
    countWord(): nodesleft(0), charsleft(0) {
        for (int i = 0; i < NHASH; i++)
            bin[i] = NULL;
    }

    void incword(char *s) {
        nodeptr p;
        int hash_val = hash(s);

        for (p = bin[hash_val]; p != NULL; p = p->next)
            if (strcmp(s, p->word) == 0) {
                (p->count)++;
                return;
            }

        add_node_in_front_of_hash_table(s, p, hash_val);
    }

    int findcount(char *s) {
        nodeptr p;
        int hash_val = hash(s);

        for (p = bin[hash_val]; p != NULL; p = p->next)
            if (strcmp(s, p->word) == 0) {
                return p->count;
            }

        return 0;
    }
};

class longDupSubStr {
private:
    static int pstrcmp(const void *p, const void *q) {
        return strcmp(*(const char**)p, *(const char**)q );
    }

    int get_common_length(char *p, char *q) {
        int i = 0;
        while (*p && (*p++ == *q++))
            i++;
        return i;
    }

    enum {MAXN=50000};
    char char_array[MAXN];
    char*suffix_array_ptr[MAXN];

    int char_size;
    int maxlen_idx;
    int maxlen;

public:
    longDupSubStr(): char_size(0), maxlen(-1) {}

    void getInputStr(char* ch) {
        strcpy(char_array, ch);

        char_size = strlen(ch);

        for(int i=0; i < char_size; i++) {
            suffix_array_ptr[i] = &char_array[i];
        }

        char_array[char_size] = 0;  // NULL
    }

    void getMaxSubStr(int occur, char* outputstr) {
        qsort(suffix_array_ptr, char_size, sizeof(char *), pstrcmp);

        int common_length = 0;
        for (int i = 0; i < char_size - occur; i++) {
            common_length = get_common_length(suffix_array_ptr[i], suffix_array_ptr[i + occur]);

            if (common_length > maxlen) {
                maxlen = common_length;
                maxlen_idx = i;
            }
        }

        strncpy(outputstr, suffix_array_ptr[maxlen_idx], maxlen);
    }

    int get_size() {
        return char_size;
    }

    char* get_char(int i) {
        return suffix_array_ptr[i];
    }

    void sortarray() {
        qsort(suffix_array_ptr, char_size, sizeof(char *), pstrcmp);
    }

    int get_maxi(){
        return maxlen_idx;
    }

    int get_maxlen(){
        return maxlen;
    }
};

class markov {
private:
    enum {MAXINPUTSIZE=43000, MAXWORDSIZE=8000, NHASH=499979, MULT=31 };
    char* _inputstr;
    char* word_ptr[MAXWORDSIZE];
    char* gen_word_ptr[MAXWORDSIZE];
    int num_words;
    char* phrase;
    int wordsleft;
    int num_gen_word;
    int hash_bin[NHASH];
    int next_link[MAXWORDSIZE];
    const int markov_order;

    static int wordncmp(const char *p, const char* q, int order = 2) {
        //TODO: How can we add k gram in sort fouction?
        //int order = k;
        //int order = 2;

        for ( ; *p == *q; p++, q++)
            if (*p == 0 && --order == 0)
                return 0;

        return *p - *q;
    }

    static int sortcmp(const void *p, const void *q) {
        return wordncmp(*(const char**)p, *(const char**)q);
    }

    char* skip_null_chars(char* char_ptr, int time) {
        for ( ; time > 0; char_ptr++)
            if (*char_ptr == '\0')  // '\0' = 0
                time--;
        return char_ptr;
    }

    unsigned int hash(char* ptr) {
        unsigned int h = 0;

        for (int time = markov_order; time > 0; ptr++) {
            h = MULT * h + *ptr;
            if (*ptr == '\0') // '\0' = 0
                time--;
        }

        return h % NHASH;
    }

    // continuously read inputstr
    void read_inputstr_and_define_words(char *inputstr) {
        int word_len =0;
        int cum_word_len =0;

        word_ptr[0] = inputstr;

        while (sscanf(inputstr + cum_word_len, "%s", word_ptr[num_words]) != EOF) {
            word_len = strlen(word_ptr[num_words]) + 1;
            cum_word_len += word_len;
            word_ptr[num_words + 1] = word_ptr[num_words] + word_len;
            num_words++;
        }
    }

    void set_gen_words_with_first_order_k_words() {
        for (int i = 0; i < markov_order; i++) {
            gen_word_ptr[num_gen_word++] = word_ptr[i];
        }
    }

    void init_bin_and_setup_bin_with_next_link() {
        for (int i = 0; i < NHASH; i++)
            hash_bin[i] = -1;

        for (int i = 0; i <= num_words - markov_order; i++) { /* check */
            /* insert new entry in front of hash */
            int j = hash(word_ptr[i]);
            next_link[i] = hash_bin[j];
            hash_bin[j] = i;
        }
    }

    int find_fist_occurrence_in_words(char *phrase) const {
        int low = -1;
        int high = num_words;
        int middle;

        while (low + 1 != high) {
                middle = (low + high) / 2;
                if (wordncmp(word_ptr[middle], phrase) < 0)
                    low = middle;
                else
                    high = middle;
            }
        return high;
    }

public:
    markov(char* inputstr, int order): num_words(0), num_gen_word(0), _inputstr(inputstr), markov_order(order){
        read_inputstr_and_define_words(inputstr);

        // append order k null characters, so the comparison function doesn't run off the end
        for (int i = 0; i < markov_order; i++)
            word_ptr[num_words][i] = '\0'; // '\0' = 0
    }

    void report_gen_text(){
        printf("\n");
        for(int i=0; i < num_gen_word; i++) {
            printf("%s ", gen_word_ptr[i]);
        }
        printf("\n");
    }

    void gen_random_text_by_hash(int num_wordgen){
        set_gen_words_with_first_order_k_words();

        wordsleft = num_wordgen;

        init_bin_and_setup_bin_with_next_link();

        phrase = _inputstr;

        char* select_word;
        for ( ; wordsleft > 0; wordsleft--) {
            int i = 0;

            for (int j = hash_bin[hash(phrase)]; j >= 0; j = next_link[j])
                // select word with same probability. see solution 12.10
                if ((wordncmp(phrase, word_ptr[j]) == 0) && (rand() % (++i) == 0))
                    select_word = word_ptr[j];

            // get next word in selected words
            phrase = skip_null_chars(select_word, 1);

            // end of sentence
            if (strlen(skip_null_chars(phrase, markov_order - 1)) == 0)
                break;

            gen_word_ptr[num_gen_word++] = skip_null_chars(phrase, markov_order - 1);
        }
    }

    void gen_random_text_by_bin_search(int num_wordgen){
        set_gen_words_with_first_order_k_words();

        wordsleft = num_wordgen;

        qsort(word_ptr, num_words, sizeof(word_ptr[0]), sortcmp);

        phrase = _inputstr;

        char* select_word;
        int occur_idx;

        for ( ; wordsleft > 0; wordsleft--) {
            occur_idx = find_fist_occurrence_in_words(phrase);

            for (int i = 0; wordncmp(phrase, word_ptr[occur_idx + i]) == 0; i++)
                if (rand() % (i+1) == 0)
                    select_word = word_ptr[occur_idx + i];

            // get next word in selected words
            phrase = skip_null_chars(select_word, 1);

            // end of sentence
            if (strlen(skip_null_chars(phrase, markov_order - 1)) == 0)
                break;

            gen_word_ptr[num_gen_word++] = skip_null_chars(phrase, markov_order - 1);
            //printf("%s\n", skip(phrase, k-1));
        }
    }

    int get_wordncmp(const char* a, const char* b, int order){
        return wordncmp(a, b, order);
    }

    void sort() {
        qsort(word_ptr, num_words, sizeof(word_ptr[0]), sortcmp);
    }

    int getnword() {
        return num_words;
    }

    char* getword(int i) {
        return word_ptr[i];
    }

    int get_num_gen_word(){
        return num_gen_word;
    }

    char* get_gen_word(int i) {
        return gen_word_ptr[i];
    }
};

class markovlet {
private:
    enum {MAXSIZE=5000000};
    char outputchar[MAXSIZE];
    int inputlen;
    const int maxlen;
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
