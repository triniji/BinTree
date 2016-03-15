#ifndef COMPARATOR_H_INCLUDED
#define COMPARATOR_H_INCLUDED

class IntegerComparator
{
public:
    static int compare(int first, int second);
private:
    IntegerComparator();
};

int IntegerComparator::compare(int first, int second)
{
    if (first < second)
        return -1;
    if (first > second)
        return 1;
    else
        return 0;
}
#endif // COMPARATOR_H_INCLUDED
