const express = require('express');
const router = express.Router();
const Tree  = require('../models/treeMode');
const db = require('../models/database');

const tree = new Tree(db);

router.get("/getAllTree", async (req, res) => {
    try {
        let AllTree = await tree.getAllTree();
        res.status(201).json({message: "all threes:",AllTree});

    } catch (error) {
        console.log(error);
    }

});


router.post("/add", async (req, res) => {
    try {
        const { name } = req.body;
        await tree.createTree(name);
        res.status(201).json({message: "create tree success"});

    } catch (error) {
        console.log(error);
    }

});

router.delete("/delete/:id", async (req, res) => {
    try {
        const { id } = req.params;
        await tree.deleteTree(id);
        res.status(200).json({ message: "Tree deleted successfully" });
    } catch (error) {
        console.log(error);
        res.status(500).json({ message: "Error deleting tree" });
    }
});


router.put("/update/:id", async (req, res) => {
    try {
        const { id } = req.params;
        const { name } = req.body;
        await tree.updateTreeName(id, name);
        res.status(200).json({ message: "Tree name updated successfully" });
    } catch (error) {
        console.log(error);
        res.status(500).json({ message: "Error updating tree name" });
    }
});




module.exports = router;