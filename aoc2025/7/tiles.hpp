#include <vector>
#pragma once

const std::vector<std::vector<bool>> splitter = {{0, 1, 0},
                                           {1, 1, 1},
                                           {1, 1, 1},
                                           {1, 0, 1},
                                           {0, 0, 0},
                                           {0, 0, 0}};

const std::vector<std::vector<bool>> split_l = {{1, 0, 0},
                                          {1, 0, 0},
                                          {1, 1, 0},
                                          {1, 1, 0},
                                          {1, 1, 1},
                                          {1, 1, 1}};

const std::vector<std::vector<bool>> split_r = {{0, 0, 1},
                                          {0, 0, 1},
                                          {0, 1, 1},
                                          {0, 1, 1},
                                          {1, 1, 1},
                                          {1, 1, 1}};
const std::vector<std::vector<bool>> split_both = {{1, 0, 1},
                                             {1, 0, 1},
                                             {1, 1, 1},
                                             {1, 1, 1},
                                             {1, 1, 1},
                                             {1, 1, 1}};


const std::vector<std::vector<bool>> src = {{1, 1, 1},
                                      {1, 1, 1},
                                      {1, 1, 1},
                                      {1, 1, 1},
                                      {1, 0, 1},
                                      {0, 0, 0}};
const std::vector<std::vector<bool>> square = {{1, 1, 1},
                                         {1, 1, 1},
                                         {1, 1, 1},
                                         {1, 1, 1},
                                         {1, 1, 1},
                                         {1, 1, 1}};


