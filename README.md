# OSRM_PLAN

以下是更详细的介绍，以帮助您构建和使用OSRM前后端项目：

1. 克隆仓库：打开终端，并通过以下命令克隆OSRM的前端和后端GitHub仓库到本地：

   ```
   git clone https://github.com/Project-OSRM/osrm-frontend.git
   git clone https://github.com/Project-OSRM/osrm-backend.git
   ```

2. 构建后端：

   - 进入 `osrm-backend` 目录，其中包含OSRM后端项目的代码。
   - 根据操作系统和编译器要求，安装所需的依赖项。通常需要CMake、Boost和STXXL等库。
   - 使用CMake生成Makefile或IDE项目文件，以便构建可执行文件。
   - 建议在构建之前阅读并遵循 `osrm-backend` 仓库中的指南和文档。

3. 准备路网数据：

   - 从OSRM官方网站（[https://download.geofabrik.de](https://download.geofabrik.de/)）上下载适合您需求区域的地图数据文件（例如`.osm.pbf`格式）。

   - 运行OSRM提供的工具，如 `osrm-extract` 和 `osrm-contract` 对地图数据进行预处理。这些工具可以解析地图数据并生成用于后续计算的路网文件。

   - 可以使用类似以下命令对地图数据进行处理：

     ```
     osrm-extract map.osm.pbf -p ../profiles/car.lua
     osrm-contract map.osrm
     ```

   - 请注意，`profiles/car.lua` 是一个示例配置文件，您可以根据需要调整配置。

4. 启动后端：

   - 在完成第2和第3步之后，使用生成的可执行文件启动OSRM后端服务器。

   - 运行以下命令以启动服务器：

     ```
     ./osrm-routed map.osrm
     ```

   - 这将在默认端口（5000）上启动后端服务，可以通过`http://localhost:5000` 访问。

5. 构建前端：

   - 进入 `osrm-frontend` 目录，其中包含OSRM前端项目的代码。

   - 运行以下命令安装前端依赖项：

     ```
     npm install
     ```

6. 配置后端地址：

   - 在前端项目中找到配置文件（一般是 `.env` 文件），它可能位于根目录或 `src` 目录下。

   - 将后端的地址和端口配置为正确的值，以便与OSRM后端服务器进行通信。例如：

     ```
     复制代码REACT_APP_BACKEND_URL=http://localhost:5000
     ```

7. 启动前端：

   - 在终端中运行以下命令，启动OSRM前端应用程序：

     ```
     复制代码npm start
     ```

   - 这将在本地启动一个开发服务器，并在默认浏览器中打开前端应用程序。

请注意，上述步骤中的命令和配置可能会根据您的操作系统、构建环境和需求发生变化。建议仔细阅读前后端仓库中的文档和README文件，并按照它们提供的指南进行操作。
