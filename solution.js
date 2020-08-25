const { ceil, min } = Math

const getNthBackward = (kn, i, n) => {
  const index = i - n
  return index < 0 ? kn + index : index
}

const getNthForward = (kn, i, n) => {
  const index = i + n
  return index >= kn ? index - kn : index
}

const getLeastMoves = (kn, needAry, hasAry) => {
  let moves = 0
  for (let i = 0; i < kn; i++) {
    let tooMuch = hasAry[i] - needAry[i]
    while (tooMuch > 0) {
      for (let n = 1; n < ceil(kn / 2); n++) {
        let index = getNthBackward(kn, i, n)
        let tooLittle = hasAry[index] - needAry[index]
        if (tooLittle >= 0) {
          index = getNthForward(kn, i, n)
          tooLittle = hasAry[index] - needAry[index]
        }
        if (tooLittle < 0) {
          const totalMoved = min(tooMuch, -tooLittle)
          moves += n * totalMoved
          hasAry[i] -= totalMoved
          hasAry[index] += totalMoved
          tooMuch -= totalMoved
          break
        }
      }
    }
  }
  return moves
}

console.log(getLeastMoves(5, [1,1,1,1,1], [2,3,0,0,0]))
