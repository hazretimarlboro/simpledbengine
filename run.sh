#!/bin/bash
set -e  # stop on any error
set -x  # print commands as they run

# -------------------------
# 1️⃣ Clean old files
# -------------------------
rm -f *.o app

# -------------------------
# 2️⃣ Compile all .c files in src/
# -------------------------
g++ -c source/*.cpp

# -------------------------
# 3️⃣ Make sure object files exist
# -------------------------
if ! compgen -G "*.o" > /dev/null; then
    echo "❌ No object files found! Compilation failed."
    exit 1
fi

# -------------------------
# 4️⃣ Link all object files into executable
# -------------------------
g++ *.o -o app 

# -------------------------
# 5️⃣ Delete object files after successful build
# -------------------------
rm -f *.o

# -------------------------
# 6️⃣ Success message
# -------------------------
echo "✅ Build successful! ./app created, object files cleaned."