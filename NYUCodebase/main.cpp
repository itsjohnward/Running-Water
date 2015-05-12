//
//  Running Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#include "Running-Water.h"

int main(int argc, char *argv[])
{
    ClassDemoApp app;
    while(!app.UpdateAndRender()) {}
    return 0;
}