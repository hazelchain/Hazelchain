if [${{ matrix.os }} == "winows-latest"]; then
  cmake -B ${{github.workspace}}/build -DCMAKE_BUILD_TYPE=${{env.BUILD_TYPE}} -G "MinGW Makefiles";
  fi
if [${{ matrix.os }} == "windows-latest"]; then
  cmake -B ${{github.workspace}}/build -DCMAKE_BUILD_TYPE=${{env.BUILD_TYPE}};
  fi