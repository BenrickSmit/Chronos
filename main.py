#!/usr/bin/env python

#   Copyright 2020 Benrick Smit
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.


# This function's main purpose is to create an image to display the times each function took

import matplotlib.pyplot as plt
import pandas as pd

def main():
    # This function will obtain the predetermined path to the csv data, and read it into a graph to save
    csv_df = pd.read_csv("profiler/ChronosProfile.csv")

    plt.style.use("seaborn")
    plt.plot(csv_df["Calling Function"],csv_df["Total Time"], color="blue", label="Total Time")
    plt.plot(csv_df["Calling Function"],csv_df["Mean Time"], color="red", label="Mean Time")
    plt.title("Function Heatmap", fontsize=15, fontfamily="Liberation Mono")
    plt.ylabel("Time (s)", fontsize=15, fontfamily="Liberation Mono")
    plt.xlabel("Function Names", fontsize=15, fontfamily="Liberation Mono")
    plt.xticks(rotation=30)
    plt.legend()
    plt.tight_layout()
    plt.savefig("program_timemap.png")

    return None

main()