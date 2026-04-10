#include "../catch.hpp"
#include "Grid/COME_Mesh.hpp"

TEST_CASE("Mesh Topology and Abaqus Parsing", "[mesh]")
{
    SECTION("2D Quad Element Manual Construction")
    {
        // Setup a 2D Mesh (dim=2, spacedim=2)
        Mesh::Mesh<2, 2> mesh;

        // Add 4 nodes forming a unit square
        mesh.addNode(1, { 0.0, 0.0 });
        mesh.addNode(2, { 1.0, 0.0 });
        mesh.addNode(3, { 1.0, 1.0 });
        mesh.addNode(4, { 0.0, 1.0 });

        // Add one Quad element
        // In 2D, this should create 4 edges and 1 face
        std::array<int, 4> nodes = { 1, 2, 3, 4 };
        mesh.addElement(1, nodes);

        // Verification
        // Note: You may need to make these members public or add getters
        REQUIRE(mesh.getNodeMap().size() == 4);
        REQUIRE(mesh.getEdges().size() == 4);
        REQUIRE(mesh.getFaces().size() == 1);
    }

    SECTION("3D Abaqus Parser - Single Hexahedron")
    {
        Mesh::Mesh<3, 3> mesh;

        // Mocking a standard Abaqus file content
        // 8 nodes forming a cube, 1 hex element (C3D8)
        std::string abaqus_input =
            "*NODE\n"
            "1, 0.0, 0.0, 0.0\n"
            "2, 1.0, 0.0, 0.0\n"
            "3, 1.0, 1.0, 0.0\n"
            "4, 0.0, 1.0, 0.0\n"
            "5, 0.0, 0.0, 1.0\n"
            "6, 1.0, 0.0, 1.0\n"
            "7, 1.0, 1.0, 1.0\n"
            "8, 0.0, 1.0, 1.0\n"
            "*ELEMENT, type=C3D8, ELSET=Cube\n"
            "1, 1, 2, 3, 4, 5, 6, 7, 8\n";

        std::stringstream ss(abaqus_input);

        // This triggers the internal addNode and addElement logic
        mesh.read_abaqus(ss);

        // A single 3D Hex element should result in:
        // 8 nodes, 12 edges, 6 faces, 1 volume
        REQUIRE(mesh.getNodeMap().size() == 8);
        REQUIRE(mesh.getEdges().size() == 12);
        REQUIRE(mesh.getFaces().size() == 6);
        REQUIRE(mesh.getVolumes().size() == 1);

        // Check a specific node position to ensure parsing was correct
        // Assuming your Node class has a getPosition() method
        auto* node7 = mesh.getNodeMap().at(7);
        REQUIRE(Approx(node7->getCoordinates()[0]) == 1.0);
        REQUIRE(Approx(node7->getCoordinates()[2]) == 1.0);
    }

    SECTION("Edge and Face Uniqueness")
    {
        Mesh::Mesh<2, 2> mesh;
        mesh.addNode(1, { 0.0, 0.0 });
        mesh.addNode(2, { 1.0, 0.0 });
        mesh.addNode(3, { 1.0, 1.0 });

        // Manually adding same edge twice with reversed indices
        mesh.addEdgeIfMissing(1, 2);
        mesh.addEdgeIfMissing(2, 1);

        // Should only result in ONE edge object
        REQUIRE(mesh.getEdges().size() == 1);
    }
}