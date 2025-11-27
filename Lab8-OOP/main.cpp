#include "FileActions.hpp"
void testCopy(FileActions file)
{
    file.executeActions();
}
int main(void)
{
    FileActions file("/home/fawzybashandy/fooz.txt");
    file.registerActions({{"Write",3},{"Read",8}});
    testCopy(file);
}