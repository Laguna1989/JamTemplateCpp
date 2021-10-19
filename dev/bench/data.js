window.BENCHMARK_DATA = {
  "lastUpdate": 1634670428281,
  "repoUrl": "https://github.com/Laguna1989/JamTemplateCpp",
  "entries": {
    "Benchmark": [
      {
        "commit": {
          "author": {
            "email": "laguna.ws@gmail.com",
            "name": "Simon Weis",
            "username": "Laguna1989"
          },
          "committer": {
            "email": "laguna.ws@gmail.com",
            "name": "Simon Weis",
            "username": "Laguna1989"
          },
          "distinct": true,
          "id": "b1da46acdb5e1ac52606ab071da9fd86d16c076f",
          "message": "Remove superfluous line",
          "timestamp": "2021-10-19T20:22:02+02:00",
          "tree_id": "39fc3cb7e71d4eb9e3afeb92ddd5af50fc0d788d",
          "url": "https://github.com/Laguna1989/JamTemplateCpp/commit/b1da46acdb5e1ac52606ab071da9fd86d16c076f"
        },
        "date": 1634667833577,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GamestateWithObjects",
            "value": 5.396206446153848,
            "unit": "ms/iter",
            "extra": "iterations: 130\ncpu: 5.373977992307693 ms\nthreads: 1"
          },
          {
            "name": "BM_StartGame",
            "value": 9.721930351351357,
            "unit": "ms/iter",
            "extra": "iterations: 74\ncpu: 9.310100337837836 ms\nthreads: 1"
          },
          {
            "name": "BM_GamestateWithTweeningShapes",
            "value": 2.8299648704453624,
            "unit": "ms/iter",
            "extra": "iterations: 247\ncpu: 2.829813072874495 ms\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "laguna.ws@gmail.com",
            "name": "Simon Weis",
            "username": "Laguna1989"
          },
          "committer": {
            "email": "laguna.ws@gmail.com",
            "name": "Simon Weis",
            "username": "Laguna1989"
          },
          "distinct": true,
          "id": "1b90edc30c7869618732805e3b014d19b881c292",
          "message": "Make performance test run in release mode",
          "timestamp": "2021-10-19T21:04:40+02:00",
          "tree_id": "58ae5377d207c75ac51551e40b0ffca44a30382f",
          "url": "https://github.com/Laguna1989/JamTemplateCpp/commit/1b90edc30c7869618732805e3b014d19b881c292"
        },
        "date": 1634670427706,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GamestateWithObjects",
            "value": 5.954589452991587,
            "unit": "ms/iter",
            "extra": "iterations: 117\ncpu: 5.95418305128205 ms\nthreads: 1"
          },
          {
            "name": "BM_StartGame",
            "value": 11.48556923437516,
            "unit": "ms/iter",
            "extra": "iterations: 64\ncpu: 10.863388890625002 ms\nthreads: 1"
          },
          {
            "name": "BM_GamestateWithTweeningShapes",
            "value": 3.1981960833334213,
            "unit": "ms/iter",
            "extra": "iterations: 228\ncpu: 3.197989565789474 ms\nthreads: 1"
          }
        ]
      }
    ]
  }
}