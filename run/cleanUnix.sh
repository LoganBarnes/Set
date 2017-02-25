#!/bin/bash

cmake -E remove_directory _build
cmake -E remove_directory bin
cmake -E remove_directory lib
cmake -E remove_directory libbin
cmake -E remove_directory include
cmake -E remove_directory testbin

echo "Project clean"
