int abs (const int number)
{
    if (number < 0) return (-1 * number);
    return number;
}


const int randomNumberGenerator(const int& stop, const int& start=0)
    //RNG
{
    //Use the world/creator's name as a seed for the random generation
    return start + (rand() % (stop - start));
}