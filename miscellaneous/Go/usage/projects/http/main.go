package main

import (
	"net/http"
	"strings"

	"github.com/gin-gonic/gin"
	"github.com/google/uuid"
)

func main() {
	server := gin.Default()
	server.GET("/users", listUsers)
	server.POST("/users", addUser)
	server.GET("/user/:id", getUser)
	server.PUT("/user/:id", updateUser)
	server.DELETE("/user/:id", deleteUser)
	server.Run(":80")
}

type User struct {
	ID   string
	Name string
}

var users = []User{
	{uuid.NewString(), "flushhip"},
	{uuid.NewString(), "lisi"},
	{uuid.NewString(), "dudu"},
}

func updateUser(c *gin.Context) {
	id := c.Param("id")
	name := c.DefaultPostForm("name", "")
	for i, user := range users {
		if strings.EqualFold(id, user.ID) {
			if name == "" {
				c.JSON(http.StatusOK, gin.H{
					"message": "please input name",
				})
			} else {
				users[i].Name = name
				c.JSON(http.StatusOK, users[i])
			}
			return
		}
	}
	c.JSON(404, gin.H{
		"message": "user not found",
	})
}

func deleteUser(c *gin.Context) {
	id := c.Param("id")
	for i, user := range users {
		if strings.EqualFold(id, user.ID) {
			c.JSON(http.StatusOK, user)
			users = append(users[:i], users[i+1:]...)
			return
		}
	}
	c.JSON(http.StatusNoContent, gin.H{
		"message": "not user",
	})
}

func addUser(c *gin.Context) {
	name := c.DefaultPostForm("name", "")
	if name == "" {
		c.JSON(http.StatusOK, gin.H{
			"message": "please input name",
		})
	} else {
		id := uuid.NewString()
		user := User{id, name}
		users = append(users, user)
		c.JSON(http.StatusCreated, user)
	}
}

func getUser(c *gin.Context) {
	id := c.Param("id")
	for _, user := range users {
		if strings.EqualFold(id, user.ID) {
			c.JSON(200, user)
			return
		}
	}
	c.JSON(404, gin.H{
		"message": "user not found",
	})
}

func listUsers(c *gin.Context) {
	c.JSON(200, users)
}
